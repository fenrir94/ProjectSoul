// All Rights Reserved.


#include "Components/Combat/HeroCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "SoulGameplayTags.h"

#include "DebugHelper.h"

void UHeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}

	Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT(" hit ") + HitActor->GetActorNameOrLabel(), FColor::Green);

	OverlappedActors.AddUnique(HitActor);

	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		SoulGameplayTags::Shared_Event_MeleeHit,
		Data
	);

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		SoulGameplayTags::Player_Event_HitPause,
		FGameplayEventData()
	);

}

void UHeroCombatComponent::OnWeaponPulledFromTarget(AActor* InteractedActor)
{
}
