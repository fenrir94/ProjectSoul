// All Rights Reserved.


#include "Controllers/HeroController.h"
#include "AbilitySystem/SoulAbilitySystemComponent.h"
#include "Characters/HeroCharacter.h"
#include "GameplayEffectTypes.h"

AHeroController::AHeroController()
{
    HeroTeamID = FGenericTeamId(0);
}

void AHeroController::BeginPlay()
{
    Super::BeginPlay();

    CutScenePlayTag = FGameplayTag::RequestGameplayTag(TEXT("Shared.Status.CutScene"));

    BindASCEvents();
    
}

FGenericTeamId AHeroController::GetGenericTeamId() const
{
    return HeroTeamID;
}



void AHeroController::BindASCEvents()
{
    APawn* PlayerPawn = GetPawn();
    //AHeroCharacter* HeroCharacter = Cast<AHeroCharacter>(Pawn);
    //if (!Pawn)
    //{
    //    return;
    //}

    IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(PlayerPawn);
    if (!ASI)
    {
        return;
    }

    UAbilitySystemComponent* ASC = ASI->GetAbilitySystemComponent();
    if (!ASC)
    {
        return;
    }

    ASC->RegisterGameplayTagEvent(
        CutScenePlayTag,
        EGameplayTagEventType::NewOrRemoved
    ).AddUObject(
        this,
        &AHeroController::OnCutScenePlayingTagChanged
    );

}

void AHeroController::OnCutScenePlayingTagChanged(const FGameplayTag Tag, int32 NewCount)
{
    const bool bCutScenePlaying = (NewCount > 0);

    OnCutSceneUIStateChanged.Broadcast(bCutScenePlaying);
}