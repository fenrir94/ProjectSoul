// All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "SoulInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class SOUL_API USoulInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);

	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc);

};

template<class UserObject, typename CallbackFunc>
inline void USoulInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	checkf(InInputConfig, TEXT("Input Config data asset is null, can not proceed with binding"));

	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}
}

template<class UserObject, typename CallbackFunc>
inline void USoulInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc)
{
	checkf(InInputConfig, TEXT("Input Config data asset is null, can not proceed with binding"));

	for (const FSoulInputActionConfig& AbiltiyInputActionConfig : InInputConfig->AbilityInputActions)
	{
		if (!AbiltiyInputActionConfig.IsValid()) continue;
		
		BindAction(AbiltiyInputActionConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc, AbiltiyInputActionConfig.InputTag);
		BindAction(AbiltiyInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputReleasedFunc, AbiltiyInputActionConfig.InputTag);
	}
}
