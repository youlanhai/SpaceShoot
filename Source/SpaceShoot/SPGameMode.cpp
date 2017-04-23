// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SpaceShoot.h"
#include "SPGameMode.h"
#include "SPCharacter.h"
#include "SPMapActor.h"
#include "Engine.h"

ASPGameMode::ASPGameMode()
: Map(nullptr)
, ScreenSize(600, 740)
, bGamePause(true)
{
	// set default pawn class to our character
    DefaultPawnClass = ASPCharacter::StaticClass();
    
    if ( GEngine && GEngine->GameViewport )
    {
        FVector2D ViewportSize;
        GEngine->GameViewport->GetViewportSize(ViewportSize);
        UE_LOG(LogGame, Log, TEXT("Viewport size: %s"), *ViewportSize.ToString());
        UE_LOG(LogGame, Log, TEXT("Resolution size: %d, %d"), GSystemResolution.ResX, GSystemResolution.ResY);
    }
    
    float HalfWidth = ScreenSize.X * 0.5f;
    BoundingBox.Min.Set(-HalfWidth, 0);
    BoundingBox.Max.Set(HalfWidth, ScreenSize.Y);
}

void ASPGameMode::BeginPlay()
{
    Super::BeginPlay();
    
    ChangeMenuWidget(StartingWidgetClass);
}

void ASPGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
    if(CurrentWidget)
    {
        CurrentWidget->RemoveFromViewport();
        CurrentWidget = nullptr;
    }
    if(NewWidgetClass)
    {
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
        if(CurrentWidget != nullptr)
        {
            CurrentWidget->AddToViewport();
        }
    }
}

void ASPGameMode::OnEnemyCreate(ASPEnemy *Enemy)
{
    Enemies.Push(Enemy);
}

void ASPGameMode::OnEnemyDead(ASPEnemy *Enemy)
{
    Enemies.Remove(Enemy);
}
