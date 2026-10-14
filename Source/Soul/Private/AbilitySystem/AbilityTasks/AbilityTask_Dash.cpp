// All Rights Reserved.


#include "AbilitySystem/AbilityTasks/AbilityTask_Dash.h"
#include "Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "DebugHelper.h"

UAbilityTask_Dash* UAbilityTask_Dash::CreateDashTask(UGameplayAbility* OwningAbility, float InDuration, FVector InDirection, float InSpeed, float InCapsuleRadius, float InCapsuleHalfHeight)
{
	UAbilityTask_Dash* Task = NewAbilityTask<UAbilityTask_Dash>(OwningAbility);
	Task->Duration = InDuration;
	Task->DashSpeed = InSpeed;
	Task->DashDirection = InDirection;

	Task->OwnerCharacter = Cast<ACharacter>(OwningAbility->GetAvatarActorFromActorInfo());
	Task->CapsuleRadius = InCapsuleRadius;
	Task->CapsuleHalfHeight = InCapsuleHalfHeight;

	return Task;
}

void UAbilityTask_Dash::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (!OwnerCharacter)
	{
		OnFinished.Broadcast();
		EndTask();
		return;
	}

	ElapsedTime += DeltaTime;

	// Check End of TickTask
	if (ElapsedTime >= Duration)
	{
		Debug::Print("End");
		OnFinished.Broadcast();
		EndTask();
		return;
	}

	FVector CurrentLocation = OwnerCharacter->GetActorLocation();
	FVector StepMove = DashDirection * DashSpeed * DeltaTime;
	FVector DesiredLocation = CurrentLocation + StepMove;

	float Alpha = ElapsedTime / Duration;
	/*Debug::Print("Alpha: " + FString::SanitizeFloat(Alpha));

	FVector NewPosition = FMath::Lerp(StartLocation, TargetLocation, Alpha);
	*/
	bool bHit = CheckWall(CurrentLocation, DesiredLocation);

	if (bHit)
	{
		OnFinished.Broadcast();
		EndTask();
		return;
	}

	// Check floor and Change Location Z 
	float FloorZ;
	if (GetFloorZ(DesiredLocation, FloorZ))
	{
		DesiredLocation.Z = FloorZ + 90;
	}
	
	OwnerCharacter->SetActorLocation(DesiredLocation, false);

}

void UAbilityTask_Dash::Activate()
{
	Super::Activate();
	ElapsedTime = 0.f;
	bTickingTask = true;
}

bool UAbilityTask_Dash::CheckWall(FVector InStart, FVector InDestin)
{
	FHitResult Hit;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(OwnerCharacter);

	bool bHit = OwnerCharacter->GetWorld()->SweepSingleByChannel(
		Hit,
		InStart,
		InDestin,
		FQuat::Identity,
		ECC_WorldStatic,
		FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight),
		Params
	);

	return bHit;
}

bool UAbilityTask_Dash::GetFloorZ(FVector CheckPosition, float& OutFootZ)
{
	FHitResult FloorHit;

	const FVector TraceStart = CheckPosition + FVector(0, 0, 50);
	const FVector TraceEnd = CheckPosition - FVector(0, 0, 300);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(OwnerCharacter);

	bool bHit = OwnerCharacter->GetWorld()->LineTraceSingleByChannel(
		FloorHit,
		TraceStart,
		TraceEnd,
		ECC_Visibility,
		Params
	);

	if (bHit)
	{
		OutFootZ = FloorHit.Location.Z;
	}

	return bHit;
}
