// All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine/PostProcessVolume.h"
#include "CinematicSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SOUL_API UCinematicSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void OnWorldInitialize(UWorld* World, const UWorld::InitializationValues IVS);


	UFUNCTION(BlueprintCallable)
	void EnableSkillPostProcess();

	UFUNCTION(BlueprintCallable)
	void DisableSkillPostProcess();


private:

	void SpawnPostProcess(UWorld* World);

	void StartBlend();

	UPROPERTY()
	APostProcessVolume* SkillPPVolume = nullptr;

	float TargetBlendWeight = 1.f;
	float BlendSpeed = 4.f;

	FTimerHandle BlendTimerHandle;

};
