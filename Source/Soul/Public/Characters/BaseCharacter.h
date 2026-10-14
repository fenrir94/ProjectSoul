// All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Interfaces/PawnUIInterface.h"
#include "BaseCharacter.generated.h"

class USoulAbilitySystemComponent;
class USoulAttributeSet;
class UDataAsset_StartUpBase;
class UBoxComponent;
class UHeroUIComponent;
class UMotionWarpingComponent;

DECLARE_DELEGATE_OneParam(FOnTargetInteractedDelegate, AActor*)

UCLASS()
class SOUL_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface, public IPawnUIInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	//~ Begin IAbilitySystemInterface Interface.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface Interface

	//~ Begin PawnCombatInterface Interface.
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End PawnCombatInterface Interface

	//~ Begin PawnUIInterface Interface.
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	//~ End PawnUIInterface Interface


	FOnTargetInteractedDelegate OnWeaponHitTarget;
	FOnTargetInteractedDelegate OnWeaponPulledFromTarget;

protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

#if WITH_EDITOR
	//~ Begin UObject Interface.
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	//~ End UObject Interface.
#endif


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	USoulAbilitySystemComponent* SoulAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	USoulAttributeSet* SoulAttributeSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MotionWarping")
	UMotionWarpingComponent* MotionWarpingComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpBase> CharacterStartUpData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UBoxComponent* LeftWeaponCollisionBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	FName LeftWeaponCollisionBoxAttachBoneName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UBoxComponent* RightWeaponCollisionBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	FName RightWeaponCollisionBoxAttachBoneName;

	UFUNCTION()
	virtual void OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:
	FORCEINLINE	 USoulAbilitySystemComponent* GetSoulAbilitySystemComponent() const {
		return SoulAbilitySystemComponent;
	}
	
	FORCEINLINE	 USoulAttributeSet* GetSoulAttributeSet() const {
		return SoulAttributeSet;
	}

	FORCEINLINE UBoxComponent* GetLeftWeaponCollisionBox() const { return LeftWeaponCollisionBox; }
	FORCEINLINE UBoxComponent* GetRightWeaponCollisionBox() const { return RightWeaponCollisionBox; }
};
