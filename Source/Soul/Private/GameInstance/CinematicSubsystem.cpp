// All Rights Reserved.


#include "GameInstance/CinematicSubsystem.h"

void UCinematicSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	//Collection.InitializeDependency<UWorldSubsystem>();
	FWorldDelegates::OnPostWorldInitialization.AddUObject(
		this,
		&UCinematicSubsystem::OnWorldInitialize
	);
}

void UCinematicSubsystem::Deinitialize()
{
}

void UCinematicSubsystem::OnWorldInitialize(UWorld* World, const UWorld::InitializationValues IVS)
{
	if (!World || World->IsPreviewWorld()) return;
	SpawnPostProcess(World);
}

void UCinematicSubsystem::SpawnPostProcess(UWorld* World)
{
	if (!World || SkillPPVolume) return;

	SkillPPVolume = World->SpawnActor<APostProcessVolume>();
	SkillPPVolume->bUnbound = true;
	SkillPPVolume->BlendWeight = 0.f;
	SkillPPVolume->Priority = 999;
}

void UCinematicSubsystem::StartBlend()
{
	if (!GetWorld()) return;

	GetWorld()->GetTimerManager().ClearTimer(BlendTimerHandle);

	GetWorld()->GetTimerManager().SetTimer(
		BlendTimerHandle,
		[this]()
		{
			if (!SkillPPVolume) return;

			float Current = SkillPPVolume->BlendWeight;
			float NewValue = FMath::FInterpTo(
				Current,
				TargetBlendWeight,
				GetWorld()->GetDeltaSeconds(),
				BlendSpeed
			);

			SkillPPVolume->BlendWeight = NewValue;

			if (FMath::IsNearlyEqual(NewValue, TargetBlendWeight, 0.01f))
			{
				SkillPPVolume->BlendWeight = TargetBlendWeight;
				GetWorld()->GetTimerManager().ClearTimer(BlendTimerHandle);
			}
		},
		0.016f, // 60FPS
		true
	);

}

void UCinematicSubsystem::EnableSkillPostProcess()
{
	if (!SkillPPVolume) return;

	FPostProcessSettings& PPS = SkillPPVolume->Settings;

	PPS.bOverride_ColorGamma = true;
	PPS.ColorGamma = FVector4(0.6f, 0.6f, 0.6f, 1.f);

	PPS.bOverride_VignetteIntensity = true;
	PPS.bOverride_VignetteIntensity = 0.8f;

	TargetBlendWeight = 1.f;

	StartBlend();
}

void UCinematicSubsystem::DisableSkillPostProcess()
{
	if (!SkillPPVolume) return;

	TargetBlendWeight = 0.f;
	StartBlend();
}
