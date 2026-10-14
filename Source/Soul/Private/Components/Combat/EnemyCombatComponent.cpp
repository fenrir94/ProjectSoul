// All Rights Reserved.


#include "Components/Combat/EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "SoulGameplayTags.h"
#include "SoulFunctionLibrary.h"
#include "Characters/EnemyCharacter.h"


#include "DebugHelper.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}

	Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT(" is Hitting ") + HitActor->GetActorNameOrLabel(), FColor::Green);

	OverlappedActors.AddUnique(HitActor);

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;

	if (USoulFunctionLibrary::NativeDoesActorHaveTag(HitActor, SoulGameplayTags::Player_Status_Invincible))
	{
		return;
	}

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		SoulGameplayTags::Shared_Event_MeleeHit,
		EventData
	);

}
