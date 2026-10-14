// All Rights Reserved.


#include "Components/TargetLock/SoulTargetLockComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "Characters/EnemyCharacter.h"
//#include "Controllers/CameraManager/HeroCameraManager.h"
#include "Widgets/SoulWidgetBase.h"
#include "SoulFunctionLibrary.h"
#include "SoulGameplayTags.h"

USoulTargetLockComponent::USoulTargetLockComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MaxLockDistance = 3000.f;
	BoxTraceExtent = FVector(2000.f, 2000.f, 500.f);
	RotationInterpSpeed = 10.f;

	bLockEnabled = false;
	CurrentTarget = nullptr;
	TargetLockWidget = nullptr;
	TargetLockWidgetSize = FVector2D::ZeroVector;
}

void USoulTargetLockComponent::EnableTargetLock()
{
	bLockEnabled = true;
	FindAvailableTargets();
	CurrentTarget = GetNearestTarget();

	//if (APlayerController* PC = Cast<APlayerController>(GetOwner()->GetInstigatorController()))
	//{
	//	PC->SetIgnoreLookInput(true);

	//	if (AHeroCameraManager* CameraManager = Cast<AHeroCameraManager>(PC->PlayerCameraManager))
	//	{
	//		CameraManager->SetLockOnTarget(CurrentTarget);
	//	}
	//}

	UpdateTargetLockWidget();

	OnTargetChanged.Broadcast(CurrentTarget);
}

void USoulTargetLockComponent::DisableTargetLock()
{
	bLockEnabled = false;
	CurrentTarget = nullptr;

	ClearTargetLockWidget();

	//if (APlayerController* PC = Cast<APlayerController>(GetOwner()->GetInstigatorController()))
	//{
	//	PC->SetIgnoreLookInput(false);

	//	if (AHeroCameraManager* CameraManager = Cast<AHeroCameraManager>(PC->PlayerCameraManager))
	//	{
	//		CameraManager->ClearLockOnTarget();
	//	}
	//}

	OnTargetChanged.Broadcast(nullptr);
}

void USoulTargetLockComponent::SwitchTarget(bool bNext)
{
	if (AvailableTargets.Num() == 0|| !CurrentTarget )return;

	int32 CurrentIndex = AvailableTargets.IndexOfByKey(CurrentTarget);
	if (CurrentIndex == INDEX_NONE) return;

	int32 NewIndex = bNext ? (CurrentIndex + 1) % AvailableTargets.Num() : (CurrentIndex - 1 + AvailableTargets.Num()) % AvailableTargets.Num();

	CurrentTarget = AvailableTargets[NewIndex];
	OnTargetChanged.Broadcast(CurrentTarget);

}

void USoulTargetLockComponent::BroadcastTargetLost()
{
	OnTargetLost.Broadcast();
}

void USoulTargetLockComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USoulTargetLockComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bLockEnabled)
	{
		ClearTargetLockWidget();
		return;
	}
	
	if( USoulFunctionLibrary::NativeDoesActorHaveTag(CurrentTarget, SoulGameplayTags::Shared_Status_Dead) ||
		USoulFunctionLibrary::NativeDoesActorHaveTag(GetOwner(), SoulGameplayTags::Shared_Status_Dead)
		)
	{
		DisableTargetLock();
		return;
	}


	if (!CurrentTarget || !IsValid(CurrentTarget))
	{
		FindAvailableTargets();
		AActor* NewTarget = GetNearestTarget();

		if (NewTarget)
		{
			CurrentTarget = NewTarget;
			OnTargetChanged.Broadcast(CurrentTarget);
		}
		else 
		{

			DisableTargetLock();
			OnTargetLost.Broadcast();
			
			//if (APlayerController* PC = Cast<APlayerController>(GetOwner()->GetInstigatorController()))
			//{
			//	if (AHeroCameraManager* CameraManager = Cast<AHeroCameraManager>(PC->PlayerCameraManager))
			//	{
			//		CameraManager->ClearLockOnTarget();
			//	}
			//}

			return;
		}
	}

	const bool bShouldOverrideRotation = !USoulFunctionLibrary::NativeDoesActorHaveTag(GetOwner(), SoulGameplayTags::Player_Status_Blink)
				&& !USoulFunctionLibrary::NativeDoesActorHaveTag(GetOwner(), SoulGameplayTags::Player_Status_Rolling);
		
	if (bShouldOverrideRotation)
	{
		UpdateCameraRotation(DeltaTime);
	}

	UpdateTargetLockWidget();
}

void USoulTargetLockComponent::FindAvailableTargets()
{
	AvailableTargets.Empty();

	ACharacter* OwnerChar = Cast<ACharacter>(GetOwner());
	if (!OwnerChar) return;

	FVector Origin = OwnerChar->GetActorLocation();
	TArray<AActor*> OverlappingActors;

	UKismetSystemLibrary::BoxOverlapActors(GetWorld(), Origin, BoxTraceExtent, TraceObjectTypes, nullptr, TArray<AActor*>{OwnerChar}, OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		if (Actor && Actor != OwnerChar)
		{
			float Dist = FVector::Dist(Origin, Actor->GetActorLocation());
			if (Dist <= MaxLockDistance)
			{
				AvailableTargets.Add(Actor);
			}
		}
	}
}

AActor* USoulTargetLockComponent::GetNearestTarget() const
{
	if (AvailableTargets.Num() == 0) return nullptr;

	ACharacter* OwnerChar = Cast<ACharacter>(GetOwner());
	if (!OwnerChar) return nullptr;

	AActor* Nearest = nullptr;
	float MinDist = TNumericLimits<float>::Max();

	for (AActor* Actor : AvailableTargets)
	{
		if (Actor->Implements<UPawnTargetableInterface>())
		{
			IPawnTargetableInterface* Targetable = Cast<IPawnTargetableInterface>(Actor);
		
			if (Targetable && Targetable->IsTargetable())
			{
				float Dist = FVector::Dist(OwnerChar->GetActorLocation(), Actor->GetActorLocation());
				if (Dist < MinDist)
				{
					MinDist = Dist;
					Nearest = Actor;
				}
			}
		}
	}
	return Nearest;
}

void USoulTargetLockComponent::UpdateTargetLockWidget()
{
	if (!TargetLockWidgetClass) return;

	if (!TargetLockWidget && CurrentTarget)
	{
		APlayerController* PC = Cast<APlayerController>(GetOwner()->GetInstigatorController());
		if (PC)
		{
			TargetLockWidget = CreateWidget<USoulWidgetBase>(PC, TargetLockWidgetClass);
			TargetLockWidget->AddToViewport();
		}
	}

	if (!TargetLockWidget || !CurrentTarget)
	{
		ClearTargetLockWidget();
		return;
	}

	USkeletalMeshComponent* Mesh = CurrentTarget->FindComponentByClass<USkeletalMeshComponent>();
	if (!Mesh) return;

	const FName SocketName = FName("Aim_Target");

	FVector SocketWorldLocation = Mesh->DoesSocketExist(SocketName) ? Mesh->GetSocketLocation(SocketName) : CurrentTarget->GetActorLocation();

	FVector2D ScreenPos;
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(
		Cast<APlayerController>(GetOwner()->GetInstigatorController()),
		SocketWorldLocation,
		ScreenPos,
		true
	);

	if (TargetLockWidgetSize == FVector2D::ZeroVector)
	{
		TargetLockWidgetSize = FVector2D(10.f, 10.f);
	}

	ScreenPos -= TargetLockWidgetSize / 2.f;
	TargetLockWidget->SetPositionInViewport(ScreenPos, false);

}

void USoulTargetLockComponent::ClearTargetLockWidget()
{
	if (TargetLockWidget)
	{
		TargetLockWidget->RemoveFromParent();
		TargetLockWidget = nullptr;
	}
}

void USoulTargetLockComponent::UpdateCameraRotation(float DeltaTime)
{
	if (!CurrentTarget) return;

	ACharacter* OwnerChar = Cast<ACharacter>(GetOwner());
	if (!OwnerChar) return;

	APlayerController* PC = Cast<APlayerController>(OwnerChar->GetController());
	if (!PC) return;

	FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(OwnerChar->GetActorLocation(), CurrentTarget->GetActorLocation());

	LookAtRot -= FRotator(TargetLockCameraOffsetDistance, 0.f, 0.f);

	FRotator CurrentRot = PC->GetControlRotation();
	FRotator TargetRot = FMath::RInterpTo(CurrentRot, LookAtRot, DeltaTime, RotationInterpSpeed);

	PC->SetControlRotation(FRotator(TargetRot.Pitch, TargetRot.Yaw, 0.f));
	OwnerChar->SetActorRotation(FRotator(0.f, TargetRot.Yaw, 0.f));
} 
