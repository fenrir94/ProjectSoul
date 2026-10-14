// All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "GameplayTagContainer.h"
//#include "CineCameraComponent.h"
#include "HeroCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UCineCameraComponent;
class UDataAsset_InputConfig;
class UBoxComponent;
class UHeroCombatComponent;
class UHeroUIComponent;
struct FInputActionValue;
class USoulTargetLockComponent;
/**
 * 
 */
UCLASS()
class SOUL_API AHeroCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	AHeroCharacter();

	//~ Begin PawnCombatInterface Interface.
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End PawnCombatInterface Interface

	//~ Begin PawnUIInterface Interface.
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UHeroUIComponent* GetHeroUIComponent() const override;
	//~ End PawnUIInterface Interface

	UFUNCTION(BlueprintNativeEvent)
	void Input_Interact(const FInputActionValue& InputActionValue);
	virtual void Input_Interact_Implementation(const FInputActionValue& InputActionValue);

	UFUNCTION(BlueprintNativeEvent)
	void Input_OpenMenu(const FInputActionValue& InputActionValue);
	virtual void Input_OpenMenu_Implementation(const FInputActionValue& InputActionValue);


	UPROPERTY(BlueprintReadOnly, Category = "Input")
	FVector2D MovementVector;

#pragma region TraceToInteract

	//스피어 트레이스 변수

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "TraceSetting")
	float InteractRange = 200.f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "TraceSetting")
	float SphereRadius = 10.f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "TraceSetting")
	float TraceDuration = 3.0f;

	UPROPERTY()
	AActor* InteractingActor = nullptr;

#pragma endregion
protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

	virtual void OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;


private:

#pragma region Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCineCameraComponent* CineCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UHeroCombatComponent* HeroCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UHeroUIComponent* HeroUIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TargetLock", meta = (AllowPrivateAccess = "true"))
	USoulTargetLockComponent* TargetLockComponent;

#pragma endregion


#pragma region Inputs
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);

	void Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue);
	void Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);
#pragma endregion

public:
	FORCEINLINE UHeroCombatComponent* GetHeroCombatComponent() const { return HeroCombatComponent; }
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE UCineCameraComponent* GetCineCamera() const { return CineCamera; }
	FORCEINLINE USoulTargetLockComponent* GetTargetLockComponent() const { return TargetLockComponent; }
};
