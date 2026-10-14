// All Rights Reserved.


#include "DataAssets/StartUpData/DataAsset_StartUpBase.h"
#include "AbilitySystem/SoulAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/SoulGameplayAbility.h"

void UDataAsset_StartUpBase::GiveToAbilitySystemComponent(USoulAbilitySystemComponent* InASCToGive, int32 Applylevel)
{
	check(InASCToGive);

	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, Applylevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, Applylevel);

	if (!StartUpGameplayEffect.IsEmpty())
	{
		for (const TSubclassOf<UGameplayEffect>& EffectClass : StartUpGameplayEffect)
		{
			if (!EffectClass) continue;

			UGameplayEffect* EffectCDO = EffectClass->GetDefaultObject<UGameplayEffect>();
			InASCToGive->ApplyGameplayEffectToSelf(
				EffectCDO,
				Applylevel, 
				InASCToGive->MakeEffectContext()
			);
		}
	}
}

void UDataAsset_StartUpBase::GrantAbilities(const TArray<TSubclassOf<USoulGameplayAbility>>& InAbilitiesToGive, USoulAbilitySystemComponent* InASCToGive, int32 Applylevel)
{
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<USoulGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = Applylevel;

		InASCToGive->GiveAbility(AbilitySpec);
	}
}
