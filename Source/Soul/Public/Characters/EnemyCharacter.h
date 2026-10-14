// All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Interfaces/PawnTargetableInterface.h"
#include "GameplayTagContainer.h"
#include "EnemyCharacter.generated.h"

class UEnemyCombatComponent;
class UEnemyUIComponent;

/**
 * 
 */
UCLASS()
class SOUL_API AEnemyCharacter : public ABaseCharacter, public IPawnTargetableInterface
{
	GENERATED_BODY()
	
public:
	AEnemyCharacter();

	//~ Begin PawnCombatInterface Interface.
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End PawnCombatInterface Interface

	//~ Begin PawnUIInterface Interface.
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UEnemyUIComponent* GetEnemyUIComponent() const override;
	//~ End PawnUIInterface Interface

	//~ Begin IPawnTargetableInterface Interface.
	virtual FVector GetTargetLocation() const override;
	virtual bool IsTargetable() const override;
	//~ End IPawnTargetableInterface Interface

protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UEnemyUIComponent* EnemyUIComponent;


	virtual void OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:
	void InitEnemyStartUpData();

public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};
