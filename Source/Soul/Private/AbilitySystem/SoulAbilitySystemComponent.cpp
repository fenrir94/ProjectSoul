// All Rights Reserved.


#include "AbilitySystem/SoulAbilitySystemComponent.h"
#include "SoulGameplayTags.h"

#include "DebugHelper.h"

void USoulAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
	{
		return;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InInputTag)) continue;

		if (InInputTag.MatchesTag(SoulGameplayTags::InputTag_Toggleable))
		{
			if (AbilitySpec.IsActive())
			{
				CancelAbilityHandle(AbilitySpec.Handle);
			}
			else
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
		else 
		{
			TryActivateAbility(AbilitySpec.Handle);
		}

	
	}
}

void USoulAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
	{
		return;
	}

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InInputTag)) continue;
		
		if (AbilitySpec.IsActive())
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

bool USoulAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate)
{
	check(AbilityTagToActivate.IsValid());
	//Debug::Print(AbilityTagToActivate.ToString(), FColor::Blue);

	TArray<FGameplayAbilitySpec*> FoundAbilitySpecs;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityTagToActivate.GetSingleTagContainer(), FoundAbilitySpecs);

	if (!FoundAbilitySpecs.IsEmpty())
	{
		const int32 RandomAbilityIndex = FMath::RandRange(0, FoundAbilitySpecs.Num() -1);
		FGameplayAbilitySpec* SpecToActivate = FoundAbilitySpecs[RandomAbilityIndex];

		check(SpecToActivate);

		if (!SpecToActivate->IsActive())
		{
			//Debug::Print(TEXT("IsActive"), FColor::Red);
			return TryActivateAbility(SpecToActivate->Handle);
		}
	}
	else
	{
		//Debug::Print(TEXT("Empty"), FColor::Red);
	}

	return false;
}
