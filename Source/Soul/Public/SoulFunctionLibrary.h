// All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SoulFunctionLibrary.generated.h"

class USoulAbilitySystemComponent;
class UPawnCombatComponent;

UENUM()
enum class ESoulConfirmType : uint8
{
	Yes,
	No
};

UENUM()
enum class ESoulValidType : uint8
{
	Valid,
	Invalid
};

UENUM()
enum class ESoulSuccessType : uint8
{
	Successful,
	Failed
};

/**
 * 
 */
UCLASS()
class SOUL_API USoulFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static USoulAbilitySystemComponent* NativeGetSoulASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Soul|FuncitonLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);


	UFUNCTION(BlueprintCallable, Category = "Soul|FuncitonLibrary")
	static void RemoveGameplayTagToActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category = "Soul|FuncitonLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExes = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, ESoulConfirmType& OutConfirmType);

	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Soul|FuncitonLibrary", meta = (DisplayName = "Get Pawn Combat Component From Actor", ExpandEnumAsExes = "OutValidType"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor, ESoulValidType& OutValidType);

	UFUNCTION(BlueprintPure, Category = "Soul|FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);

	UFUNCTION(BlueprintPure, Category = "Soul|FunctionLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference);

	UFUNCTION(BlueprintCallable, Category = "Soul|FunctionLibrary")
	static void CancelAbilitiesWithTag(UAbilitySystemComponent* ASC, FGameplayTag AbilityTag);

};
