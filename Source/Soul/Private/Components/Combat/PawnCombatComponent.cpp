// All Rights Reserved.


#include "Components/Combat/PawnCombatComponent.h"
#include "Characters/BaseCharacter.h"
#include "Components/BoxComponent.h"

void UPawnCombatComponent::ToggleWeaponBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	ABaseCharacter* OwningCharacter = GetOwningPawn<ABaseCharacter>();

	check(OwningCharacter);

	UBoxComponent* LeftWeaponCollisionBox = OwningCharacter->GetLeftWeaponCollisionBox();
	UBoxComponent* RightWeaponCollisionBox = OwningCharacter->GetRightWeaponCollisionBox();

	check(LeftWeaponCollisionBox && RightWeaponCollisionBox);

	switch (ToggleDamageType)
	{
	case EToggleDamageType::LeftWeapon:
		LeftWeaponCollisionBox->SetCollisionEnabled(bShouldEnable? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	case EToggleDamageType::RightWeapon:
		RightWeaponCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	default:
		break;
	}

	if (!bShouldEnable)
	{
		OverlappedActors.Empty();
	}
}

void UPawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{
}

void UPawnCombatComponent::OnWeaponPulledFromTarget(AActor* InteractedActor)
{
}
