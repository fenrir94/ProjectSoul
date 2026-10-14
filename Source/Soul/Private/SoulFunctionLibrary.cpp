// All Rights Reserved.


#include "SoulFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem\SoulAbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"
#include "GenericTeamAgentInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "SoulGameplayTags.h"

#include "DebugHelper.h"

USoulAbilitySystemComponent* USoulFunctionLibrary::NativeGetSoulASCFromActor(AActor* InActor)
{
	if (!InActor)
	{
		return nullptr;
	}
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor);
	if (!ASC)
	{
		return nullptr;
	}
	
	USoulAbilitySystemComponent* SoulASC = Cast<USoulAbilitySystemComponent>(ASC);
	if (!SoulASC)
	{
		return nullptr;
	}

	return SoulASC;
}

void USoulFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	USoulAbilitySystemComponent* ASC = NativeGetSoulASCFromActor(InActor);

	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void USoulFunctionLibrary::RemoveGameplayTagToActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	USoulAbilitySystemComponent* ASC = NativeGetSoulASCFromActor(InActor);

	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

bool USoulFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	USoulAbilitySystemComponent* ASC = NativeGetSoulASCFromActor(InActor);

	if (!ASC)
	{
		return false;
	}

	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void USoulFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, ESoulConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? ESoulConfirmType::Yes : ESoulConfirmType::No;
}

UPawnCombatComponent* USoulFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	//check(InActor);

	if (IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}

	return nullptr;
}

UPawnCombatComponent* USoulFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor, ESoulValidType& OutValidType)
{
	UPawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);

	OutValidType = CombatComponent ? ESoulValidType::Valid : ESoulValidType::Invalid;

	return CombatComponent;
}

bool USoulFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);

	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());
	
	if (QueryTeamAgent && TargetTeamAgent)
	{
		//Debug::Print(TEXT("Qeury Team ID: " + LexToString(QueryTeamAgent->GetGenericTeamId().GetId())), FColor::Red);
		//Debug::Print(TEXT("Target Team ID: " + LexToString(TargetTeamAgent->GetGenericTeamId().GetId())), FColor::Red);
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}

	return false;
}

FGameplayTag USoulFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference)
{
	const FVector VictimForward = InVictim->GetActorForwardVector();
	const FVector VictimToAttackerNormalized = (InAttacker->GetActorLocation() - InVictim->GetActorLocation()).GetSafeNormal();

	const float DotResult = FVector::DotProduct(VictimForward, VictimToAttackerNormalized);
	OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossResult = FVector::CrossProduct(VictimForward, VictimToAttackerNormalized);
	
	if (CrossResult.Z < 0.f)
	{
		OutAngleDifference *= -1.f;
	}

	if (OutAngleDifference >= -45.f && OutAngleDifference <= 45.f)
	{
		return SoulGameplayTags::Shared_Status_HitReact_Front;
	}
	else if (OutAngleDifference < -45.f && OutAngleDifference >= -135.f)
	{
		return SoulGameplayTags::Shared_Status_HitReact_Left;
	}
	else if (OutAngleDifference < -135.f && OutAngleDifference > 135.f)
	{
		return SoulGameplayTags::Shared_Status_HitReact_Back;
	}
	else if (OutAngleDifference > 45.f && OutAngleDifference <= -135.f)
	{
		return SoulGameplayTags::Shared_Status_HitReact_Right;
	}


	return SoulGameplayTags::Shared_Status_HitReact_Front;
}

void USoulFunctionLibrary::CancelAbilitiesWithTag(UAbilitySystemComponent* ASC, FGameplayTag AbilityTag)
{
	if (!ASC || !AbilityTag.IsValid()) return;

	for (const FGameplayAbilitySpec& Spec : ASC->GetActivatableAbilities())
	{
		//if (Spec.Ability && Spec.Ability->AbilityTags.HasTag(AbilityTag))
		if (Spec.Ability && Spec.Ability->GetAssetTags().HasTag(AbilityTag))
		{
			ASC->CancelAbility(Spec.Ability);
		}
	}
}
