// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShoot.h"
#include "SPExplose.h"


ASPExplose::ASPExplose()
{
    UPaperFlipbookComponent *Component = GetRenderComponent();
    if(Component != nullptr)
    {
        Component->SetLooping(false);
        Component->OnFinishedPlaying.AddDynamic(this, &ASPExplose::OnAnimationFinished);
    }
    
    static ConstructorHelpers::FObjectFinderOptional<USoundWave> SoundAsset(TEXT("/Game/SpaceShoot/Sound/explode_1"));
    
    AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
    if(AudioComponent != nullptr && SoundAsset.Succeeded())
    {
        AudioComponent->SetSound(SoundAsset.Get());
        AudioComponent->OnAudioFinished.AddDynamic(this, &ASPExplose::OnSoundFinished);
    }
}

void ASPExplose::OnAnimationFinished()
{
    bAnimationEnd = true;
    TryDestroy();
}

void ASPExplose::OnSoundFinished()
{
    bSoundEnd = true;
    TryDestroy();
}

void ASPExplose::TryDestroy()
{
    if((AudioComponent->Sound == nullptr || bSoundEnd) &&
       (GetRenderComponent()->GetFlipbook() == nullptr || bAnimationEnd))
    {
        Destroy();
    }
}
