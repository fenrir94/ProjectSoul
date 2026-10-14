// All Rights Reserved.


#include "Controllers/CameraManager/HeroCameraManager.h"
#include "GameFramework/SpringArmComponent.h"
#include "Characters/HeroCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"

void AHeroCameraManager::UpdateCamera(float DeltaTime)
{
	Super::UpdateCamera(DeltaTime);

	if (bIsTargetLocked && TargetActor && Hero && SpringArm)
	{
		FVector PlayerLoc = Hero->GetActorLocation();
		FVector CameraLoc = FollowCamera->GetComponentLocation();
		FVector TargetLoc = TargetActor->GetActorLocation();

		float Distance = FVector::Dist(PlayerLoc, TargetLoc);

		float PivotAdjustZ = FMath::GetMappedRangeValueClamped(FVector2D(0.f, 800.f), FVector2D(200.f, 0.f), Distance);
		SpringArm->TargetOffset.Z = BaseTargetOffsetZ + PivotAdjustZ;

		float TargetArmLength = FMath::GetMappedRangeValueClamped(FVector2D(0.f, 800.f), FVector2D(200.f, 300.f), Distance);
		SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, TargetArmLength, DeltaTime, 5.f);

		FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(CameraLoc, TargetLoc);

		FRotator CurrentRot = FollowCamera->GetComponentRotation();
		FRotator TargetRot = FRotator(LookAtRot.Pitch, CurrentRot.Yaw, CurrentRot.Roll);
		
		FRotator NewRot = FMath::RInterpTo(CurrentRot, TargetRot, DeltaTime, 2.f);
		FollowCamera->SetWorldRotation(NewRot);
	}
	else if (bIsReturningFromLock && SpringArm && FollowCamera)
	{
		/*ReturnAlpha = FMath::Clamp(ReturnAlpha + DeltaTime * ReturnInterpSpeed, 0.f, 1.f);
		SpringArm->TargetArmLength = FMath::Lerp(SpringArm->TargetArmLength, TargetReturnArmLength, ReturnAlpha);
		SpringArm->TargetOffset = FMath::Lerp(SpringArm->TargetOffset, TargetReturnOffset, ReturnAlpha);
		FRotator CurrentRot = FollowCamera->GetComponentRotation();
		FRotator NewRot = FMath::RInterpTo(CurrentRot, TargetReturnRotation, DeltaTime, ReturnInterpSpeed);
		FollowCamera->SetWorldRotation(NewRot);*/

		SpringArm->TargetArmLength = FMath::Lerp(SpringArm->TargetArmLength, TargetReturnArmLength, ReturnAlpha);
		SpringArm->TargetOffset = FMath::Lerp(SpringArm->TargetOffset, TargetReturnOffset, ReturnAlpha);

		FRotator CurrentRot = SpringArm->GetRelativeRotation();
		FRotator NewRot = FMath::RInterpTo(CurrentRot, TargetReturnRotation, DeltaTime, ReturnInterpSpeed);
		SpringArm->SetRelativeRotation(NewRot);

		FollowCamera->SetRelativeLocation(FVector::ZeroVector);
		FollowCamera->SetRelativeRotation(FRotator::ZeroRotator);

		if (ReturnAlpha >= 0.99f)
		{
			bIsReturningFromLock = false;
			SpringArm->TargetArmLength = TargetReturnArmLength;
			SpringArm->TargetOffset = TargetReturnOffset;
			FollowCamera->SetWorldRotation(TargetReturnRotation);
		}
	}
	//else if (SpringArm)
	//{
	//	SpringArm->TargetOffset.Z = BaseTargetOffsetZ;
	//	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, 300.f, DeltaTime, 5.f);
	//}
}

void AHeroCameraManager::SetLockOnTarget(AActor* NewTarget)
{
	if (!bIsTargetLocked && SpringArm)
	{
		DefaultArmLength = SpringArm->TargetArmLength;
		DefaultTargetOffset = SpringArm->TargetOffset;
		DefaultRotation = FollowCamera->GetComponentRotation();
	}

	TargetActor = NewTarget;
	bIsTargetLocked = (TargetActor != nullptr);
	bIsReturningFromLock = false;
}

void AHeroCameraManager::ClearLockOnTarget()
{
	TargetActor = nullptr;
	bIsTargetLocked = false;
	ReturnAlpha = 0.f;
	bIsReturningFromLock = true;
	

	if (SpringArm)
	{
		SpringArm->TargetArmLength = DefaultArmLength;
		SpringArm->TargetOffset = DefaultTargetOffset;
		SpringArm->bUsePawnControlRotation = true;
		//SpringArm->TargetArmLength = 300.f;
	}

	if (FollowCamera)
	{
		//FollowCamera->SetRelativeRotation(FRotator::ZeroRotator);
		TargetReturnRotation = DefaultRotation;
	}
}

void AHeroCameraManager::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = GetOwningPlayerController();
	if (PC)
	{
		Hero = Cast<AHeroCharacter>(PC->GetPawn());
		if (Hero)
		{
			SpringArm = Hero->GetCameraBoom();
			FollowCamera = Hero->GetFollowCamera();
		}

	}
}
