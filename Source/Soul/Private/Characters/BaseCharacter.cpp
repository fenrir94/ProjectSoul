// All Rights Reserved.


#include "Characters/BaseCharacter.h"
#include "AbilitySystem/SoulAbilitySystemComponent.h"
#include "AbilitySystem/SoulAttributeSet.h"
#include "Components/BoxComponent.h"
#include "SoulFunctionLibrary.h"
#include "MotionWarpingComponent.h"

#include "DebugHelper.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	SoulAbilitySystemComponent = CreateDefaultSubobject<USoulAbilitySystemComponent>(TEXT("SoulAbilitySystem"));
	SoulAttributeSet = CreateDefaultSubobject<USoulAttributeSet>(TEXT("SoulAttributeSet"));
	
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));

	LeftWeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>("LeftWeaponCollisionBox");
	LeftWeaponCollisionBox->SetupAttachment(GetMesh());
	LeftWeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftWeaponCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);

	RightWeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>("RightWeaponCollisionBox");
	RightWeaponCollisionBox->SetupAttachment(GetMesh());
	RightWeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightWeaponCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);

}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return GetSoulAbilitySystemComponent();
}

UPawnCombatComponent* ABaseCharacter::GetPawnCombatComponent() const
{
	return nullptr;
}

UPawnUIComponent* ABaseCharacter::GetPawnUIComponent() const
{
	return nullptr;
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	FString Msg = FString::Printf(TEXT("Actor %s Controller %s"), *GetName(), *NewController->GetName());

	Debug::Print(Msg);

	if (SoulAbilitySystemComponent)
	{
		
		SoulAbilitySystemComponent->InitAbilityActorInfo(this, this);

		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());
	}
}

#if WITH_EDITOR
void ABaseCharacter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, LeftWeaponCollisionBoxAttachBoneName))
	{
		LeftWeaponCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, LeftWeaponCollisionBoxAttachBoneName);
	}

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, RightWeaponCollisionBoxAttachBoneName))
	{
		RightWeaponCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, RightWeaponCollisionBoxAttachBoneName);
	}
}
#endif 


void ABaseCharacter::OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}


