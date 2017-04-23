// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShoot.h"
#include "SPPlayer.h"
#include "SPBullet.h"
#include "Engine.h"
#include "SPGameMode.h"
#include "SPBulletEmitter.h"

ASPPlayer::ASPPlayer()
{
    PrimaryActorTick.bCanEverTick = true;
    
    static ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> DefaultAsset(TEXT("/Game/SpaceShoot/Sprites/Hero/4/am"));
    if(DefaultAsset.Succeeded() && GetRenderComponent())
    {
        GetRenderComponent()->SetFlipbook(DefaultAsset.Get());
    }
    
    MoveSpeed = 10.0f;
}

ASPPlayer::~ASPPlayer()
{
}

void ASPPlayer::BeginPlay()
{
    Super::BeginPlay();

    SwitchEmitter(1);
    StartFire();
}

void ASPPlayer::Tick(float Elapse)
{
    ASPCombat::Tick(Elapse);
    
    ASPGameMode *GameMode = Cast<ASPGameMode>(UGameplayStatics::GetGameMode(this));
    if(nullptr == GameMode || GameMode->IsGamePause())
    {
        return;
    }
}

void ASPPlayer::MoveRight(float Delta)
{
    FVector Position = GetActorLocation();
    Position.X += Delta * MoveSpeed;
    SetActorLocation(Position);
    LimitInBoundary();
}

void ASPPlayer::MoveUp(float Delta)
{
    FVector Position = GetActorLocation();
    Position.Z += Delta * MoveSpeed;
    SetActorLocation(Position);
    LimitInBoundary();
}

void ASPPlayer::LimitInBoundary()
{
    ASPGameMode *GameMode = Cast<ASPGameMode>(UGameplayStatics::GetGameMode(this));
    if(GameMode != nullptr)
    {
        FVector Position = GetActorLocation();
        Position.X = FMath::Clamp(Position.X, GameMode->BoundingBox.Min.X, GameMode->BoundingBox.Max.X);
        Position.Z = FMath::Clamp(Position.Z, GameMode->BoundingBox.Min.Y, GameMode->BoundingBox.Max.Y);
        SetActorLocation(Position);
    }
}
