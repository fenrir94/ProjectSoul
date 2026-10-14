// All Rights Reserved.


#include "AbilitySystem/Abilities/HeroGameplayAbility_TargetLock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Characters/HeroCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/SoulWidgetBase.h"
#include "Controllers/HeroController.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/SizeBox.h"
#include "SoulFunctionLibrary.h"
#include "SoulGameplayTags.h"
#include "Kismet/KismetMathLibrary.h"
#include "Controllers/CameraManager/HeroCameraManager.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/TargetLock/SoulTargetLockComponent.h"

#include "DebugHelper.h"

void UHeroGameplayAbility_TargetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	//TryLockOnTarget();
	
	if (AHeroCharacter* Hero = Cast<AHeroCharacter>(GetHeroCharacterFromActorInfo()))
	{
		if (USoulTargetLockComponent* TLComp = Hero->FindComponentByClass<USoulTargetLockComponent>())
		{
			TLComp->EnableTargetLock();
			TLComp->OnTargetLost.AddDynamic(this, &UHeroGameplayAbility_TargetLock::OnTargetLost);
		}
	}

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

}

void UHeroGameplayAbility_TargetLock::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	//CleanUp();

	if (AHeroCharacter* Hero = Cast<AHeroCharacter>(GetHeroCharacterFromActorInfo()))
	{
		if (USoulTargetLockComponent* TLComp = Hero->FindComponentByClass<USoulTargetLockComponent>())
		{
			TLComp->DisableTargetLock();
			TLComp->OnTargetLost.RemoveDynamic(this, &UHeroGameplayAbility_TargetLock::OnTargetLost);
		}
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UHeroGameplayAbility_TargetLock::OnTargetLost()
{
	CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
}

//void UHeroGameplayAbility_TargetLock::OnTargetLockTick(float DeltaTime)
//{
//	AActor* Hero = GetHeroCharacterFromActorInfo();
//	if (!Hero)
//	{
//		CancelTargetLockAbility();
//		return;
//	}
//
//	if (!CurrentLockedActor || !IsValid(CurrentLockedActor))
//	{
//		CancelTargetLockAbility();
//		return;
//	}
//
//	if( USoulFunctionLibrary::NativeDoesActorHaveTag(CurrentLockedActor, SoulGameplayTags::Shared_Status_Dead) ||
//		USoulFunctionLibrary::NativeDoesActorHaveTag(GetHeroCharacterFromActorInfo(), SoulGameplayTags::Shared_Status_Dead)
//		)
//	{
//		CancelTargetLockAbility();
//		return;
//	}
//
//	const float Distance = FVector::Dist(GetHeroCharacterFromActorInfo()->GetActorLocation(), CurrentLockedActor->GetActorLocation());
//	if (Distance > MaxLockDistance)
//	{
//		GetAvailableActorsToLock();
//		AActor* NewTarget = GetNearestTargetFromAvailableActors(AvailableActorsToLock);
//
//		if (NewTarget && NewTarget != CurrentLockedActor)
//		{
//			CurrentLockedActor = NewTarget;
//			SetTargetLockWidgetPosition();
//		}
//		else
//		{
//			CancelTargetLockAbility();
//		}
//		return;
//	}
//
//
//	SetTargetLockWidgetPosition();
//
//	const bool bShouldOverrideRotation = !USoulFunctionLibrary::NativeDoesActorHaveTag(GetHeroCharacterFromActorInfo(), SoulGameplayTags::Player_Status_Blink)
//		&& !USoulFunctionLibrary::NativeDoesActorHaveTag(GetHeroCharacterFromActorInfo(), SoulGameplayTags::Player_Status_Rolling);
//
//
//	if (bShouldOverrideRotation)
//	{
//		const FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(GetHeroCharacterFromActorInfo()->GetActorLocation(),
//			CurrentLockedActor->GetActorLocation()
//		);
//
//		const FRotator CurrentControlRot = GetHeroControllerFromActorInfo()->GetControlRotation();
//		const FRotator TargetRot = FMath::RInterpTo(CurrentControlRot, LookAtRot, DeltaTime, TargetLockRotationInterpSpeed);
//
//		GetHeroControllerFromActorInfo()->SetControlRotation(FRotator(TargetRot.Pitch, TargetRot.Yaw, 0.f));
//		GetHeroCharacterFromActorInfo()->SetActorRotation(FRotator(0.f, TargetRot.Yaw, 0.f));
//	}
//}
//
//void UHeroGameplayAbility_TargetLock::TryLockOnTarget()
//{
//	GetAvailableActorsToLock();
//
//	if ( AvailableActorsToLock.IsEmpty())
//	{
//		CancelTargetLockAbility();
//		return;
//	}
//
//	CurrentLockedActor = GetNearestTargetFromAvailableActors(AvailableActorsToLock);
//
//	/* Apply Interpolation OffsetZ  */
//	APlayerController* PC = Cast<APlayerController>(GetHeroControllerFromActorInfo());
//	if (PC)
//	{
//		AHeroCameraManager* CameraManager = Cast<AHeroCameraManager>(PC->PlayerCameraManager);
//		if (CameraManager)
//		{
//			if (CurrentLockedActor)
//			{
//
//				PC->SetIgnoreLookInput(true);
//
//				//DrawTargetLockWidget();
//				//SetTargetLockWidgetPosition();
//				CameraManager->SetLockOnTarget(CurrentLockedActor);
//			}
//			else
//			{
//				//CancelTargetLockAbility();
//				CameraManager->ClearLockOnTarget();
//			}
//		}
//	}
//
//	// Before
//	if (CurrentLockedActor)
//	{
//		DrawTargetLockWidget();
//		SetTargetLockWidgetPosition();
//	}
//	else
//	{
//		CancelTargetLockAbility();
//	}
//
//}
//
//void UHeroGameplayAbility_TargetLock::GetAvailableActorsToLock()
//{
//	TArray<FHitResult> BoxTraceHits;
//
//	UKismetSystemLibrary::BoxTraceMultiForObjects(
//		GetHeroCharacterFromActorInfo(),
//		GetHeroCharacterFromActorInfo()->GetActorLocation(),
//		GetHeroCharacterFromActorInfo()->GetActorLocation() + GetHeroCharacterFromActorInfo()->GetActorForwardVector() * BoxTraceDistance,
//		TraceBoxSize / 2.f,
//		GetHeroCharacterFromActorInfo()->GetActorForwardVector().ToOrientationRotator(),
//		BoxTraceChannel,
//		false, 
//		TArray<AActor*>(),
//		bShowPersistentDebugShape? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
//		BoxTraceHits,
//		true
//	);
//
//	for (const FHitResult& TraceHit : BoxTraceHits)
//	{
//		if (AActor* HitActor = TraceHit.GetActor())
//		{
//			if (HitActor != GetHeroCharacterFromActorInfo())
//			{
//				AvailableActorsToLock.AddUnique(HitActor);
//			}
//		}
//	}
//}
//
//AActor* UHeroGameplayAbility_TargetLock::GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors)
//{
//	float CloesestDistance = 0.f;
//
//	return UGameplayStatics::FindNearestActor(GetHeroCharacterFromActorInfo()->GetActorLocation(), InAvailableActors, CloesestDistance);
//}
//
//void UHeroGameplayAbility_TargetLock::DrawTargetLockWidget()
//{
//	if (!DrawnTargetLockWidget)
//	{
//		checkf(TargetLockWidgetClass, TEXT("Forgot to assign a valid widget class in Blueprint"));
//
//		DrawnTargetLockWidget = CreateWidget<USoulWidgetBase>(GetHeroControllerFromActorInfo(), TargetLockWidgetClass);
//
//		check(DrawnTargetLockWidget);
//
//		DrawnTargetLockWidget->AddToViewport();
//	}
//}
//
//void UHeroGameplayAbility_TargetLock::SetTargetLockWidgetPosition()
//{
//	if (!DrawnTargetLockWidget || !CurrentLockedActor)
//	{
//		CancelTargetLockAbility();
//		return;
//	}
//
//	FVector2D ScreenPosition;
//	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(
//		GetHeroControllerFromActorInfo(),
//		CurrentLockedActor->GetActorLocation(),
//		ScreenPosition,
//		true
//	);
//
//	if (TargetLockWidgetSize == FVector2D::ZeroVector)
//	{
//		DrawnTargetLockWidget->WidgetTree->ForEachWidget(
//			[this](UWidget* FoundWidget)
//			{
//				if (USizeBox* FoundSizeBox = Cast<USizeBox>(FoundWidget))
//				{
//					TargetLockWidgetSize.X = FoundSizeBox->GetWidthOverride();
//					TargetLockWidgetSize.Y = FoundSizeBox->GetHeightOverride();
//
//				}
//			}
//		);
//	}
//
//	ScreenPosition -= (TargetLockWidgetSize / 2.f);
//
//	DrawnTargetLockWidget->SetPositionInViewport(ScreenPosition, false);
//}
//
//void UHeroGameplayAbility_TargetLock::CancelTargetLockAbility()
//{
//	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
//
//	if (AHeroController* PC = GetHeroControllerFromActorInfo())
//	{
//		PC->SetIgnoreLookInput(false);
//	}
//
//}
//
//void UHeroGameplayAbility_TargetLock::CleanUp()
//{
//	AvailableActorsToLock.Empty();
//
//	CurrentLockedActor = nullptr;
//
//	if (DrawnTargetLockWidget)
//	{
//		DrawnTargetLockWidget->RemoveFromParent();
//	}
//
//	DrawnTargetLockWidget = nullptr;
//
//	TargetLockWidgetSize = FVector2D::ZeroVector;
//
//	APlayerController* PC = Cast<APlayerController>(GetHeroControllerFromActorInfo());
//	if (PC)
//	{
//		AHeroCameraManager* CameraManager = Cast<AHeroCameraManager>(PC->PlayerCameraManager);
//		if (CameraManager)
//		{
//			PC->SetIgnoreLookInput(false);
//			CameraManager->ClearLockOnTarget();
//		}
//	}
//}
