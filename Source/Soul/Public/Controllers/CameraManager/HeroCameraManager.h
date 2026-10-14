// All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "HeroCameraManager.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AHeroCharacter;

/**
 * 
 */
UCLASS()
class SOUL_API AHeroCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:
	virtual void UpdateCamera(float DeltaTime) override;

	void SetLockOnTarget(AActor* NewTarget);
	void ClearLockOnTarget();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "TargetLock")
	float BaseTargetOffsetZ = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "TargetLock")
	bool bIsTargetLocked = false;

	UPROPERTY()
	AActor* TargetActor = nullptr;

	UPROPERTY()
	AHeroCharacter* Hero = nullptr;

	UPROPERTY()
	USpringArmComponent* SpringArm = nullptr;

	UPROPERTY()
	UCameraComponent* FollowCamera = nullptr;

protected:
	bool bIsReturningFromLock = false;
	float ReturnInterpSpeed = 10.f;
	float ReturnAlpha = 0.f;

	FVector TargetReturnOffset;
	float TargetReturnArmLength;
	FRotator TargetReturnRotation;


private:
	float DefaultArmLength = 300.f;
	FVector DefaultTargetOffset;
	FRotator DefaultRotation;
};
