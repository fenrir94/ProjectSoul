// All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "GameplayTagContainer.h"
#include "HeroController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCutSceneUIStateChanged, bool, CutScene);
/**
 * 
 */
UCLASS()
class SOUL_API AHeroController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:
	AHeroController();

	virtual void BeginPlay() override;

	//~ Begin IGenericTeamAgentInterface Interface.
	virtual FGenericTeamId GetGenericTeamId() const override;
	//~ End IGenericTeamAgentInterface Interface

	UPROPERTY(BlueprintAssignable, Category="UI")
	FOnCutSceneUIStateChanged OnCutSceneUIStateChanged;

protected:
	void OnCutScenePlayingTagChanged(const FGameplayTag Tag, int32 NewCount);

private:
	FGenericTeamId HeroTeamID;

	void BindASCEvents();
	FGameplayTag CutScenePlayTag;
};
