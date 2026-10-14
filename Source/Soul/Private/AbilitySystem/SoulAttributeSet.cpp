// All Rights Reserved.


#include "AbilitySystem/SoulAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "SoulFunctionLibrary.h"
#include "SoulGameplayTags.h"
#include "Interfaces/PawnUIInterface.h"
#include "Components/UI/PawnUIComponent.h"

#include "DebugHelper.h"

USoulAttributeSet::USoulAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentStamina(1.f);
	InitMaxStamina(1.f);
	InitCurrentEnergy(1.f);
	InitMaxEnergy(1.f);
	InitCurrentGuardGauge(1.f);
	InitMaxGuardGauge(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
}

void USoulAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
	}

	checkf(CachedPawnUIInterface.IsValid(), TEXT("%s didn't implement IPawnUIInterface"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();

	checkf(PawnUIComponent, TEXT("Couldn't extract a PawnUIComponent from %s"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);

		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth()/GetMaxHealth());
	}

	if (Data.EvaluatedData.Attribute == GetCurrentStaminaAttribute())
	{
		const float NewCurrentStamina = FMath::Clamp(GetCurrentStamina(), 0.f, GetMaxStamina());

		SetCurrentStamina(NewCurrentStamina);

		PawnUIComponent->OnCurrentStaminaChanged.Broadcast(GetCurrentStamina() / GetMaxStamina());

	}

	if (Data.EvaluatedData.Attribute == GetCurrentEnergyAttribute())
	{
		const float NewCurrentEnergy = FMath::Clamp(GetCurrentEnergy(), 0.f, GetMaxEnergy());

		SetCurrentEnergy(NewCurrentEnergy);

		PawnUIComponent->OnCurrentEnergyChanged.Broadcast(GetCurrentEnergy() / GetMaxEnergy());

	}

	if (Data.EvaluatedData.Attribute == GetCurrentGuardGaugeAttribute())
	{
		const float NewCurrentGuardGauge = FMath::Clamp(GetCurrentGuardGauge(), 0.f, GetMaxHealth());

		SetCurrentGuardGauge(NewCurrentGuardGauge);

		PawnUIComponent->OnCurrentGuardGaugeChanged.Broadcast(GetCurrentGuardGauge() / GetMaxGuardGauge());
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();

		Debug::Print("DamageDone", DamageDone);

		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);

		const FString DebugString = FString::Printf(
			TEXT("Old Health: %f, Damage Done: %f, NewCurrentHealth: %f"),
			OldHealth, 
			DamageDone,
			NewCurrentHealth
		);

		Debug::Print(DebugString, FColor::Green);

		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());

		if (GetCurrentHealth() == 0.f)
		{
			USoulFunctionLibrary::AddGameplayTagToActorIfNone(
				Data.Target.GetAvatarActor(),
				SoulGameplayTags::Shared_Status_Dead
			);
			

		}
	}

}