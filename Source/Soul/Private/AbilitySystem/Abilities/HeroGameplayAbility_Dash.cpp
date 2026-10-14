// All Rights Reserved.


#include "AbilitySystem/Abilities/HeroGameplayAbility_Dash.h"
#include "AbilitySystem/AbilityTasks/AbilityTask_Dash.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/HeroCharacter.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/SoulAttributeSet.h"
#include "AttributeSet.h"

#include "DebugHelper.h"

void UHeroGameplayAbility_Dash::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AHeroCharacter* Hero = GetHeroCharacterFromActorInfo();
	if (!Hero) return;
	UCharacterMovementComponent* Move = Hero->GetCharacterMovement();
	DefaultSpeed = Move->MaxWalkSpeed;
	Move->MaxWalkSpeed = DashSpeed;

	USoulAbilitySystemComponent* ASC = Cast<USoulAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
	if (!ASC) return;

	FGameplayAttribute StaminaAttr = USoulAttributeSet::GetCurrentStaminaAttribute();
	float CurrentStamina = ASC->GetNumericAttribute(StaminaAttr);

	ASC->GetGameplayAttributeValueChangeDelegate(StaminaAttr).AddUObject(this, &UHeroGameplayAbility_Dash::OnStaminaChanged);

}

void UHeroGameplayAbility_Dash::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);

	Debug::Print("Released");

}

void UHeroGameplayAbility_Dash::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	AHeroCharacter* Hero = GetHeroCharacterFromActorInfo();
	if (!Hero) return;
	Hero->GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;

}

void UHeroGameplayAbility_Dash::OnStaminaChanged(const FOnAttributeChangeData& Data)
{
	float CurrentStamina = Data.NewValue;

	if (CurrentStamina <= 0.f)
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
	}
}


