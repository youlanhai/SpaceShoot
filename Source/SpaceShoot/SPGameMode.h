// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/GameMode.h"
#include "SlateCore.h"
#include "Blueprint/UserWidget.h"
#include "SPGameMode.generated.h"

class ASPMapActor;
class ASPEnemy;

// The GameMode defines the game being played. It governs the game rules, scoring, what actors
// are allowed to exist in this game type, and who may enter the game.
//
// This game mode just sets the default pawn to be the MyCharacter asset, which is a subclass of SPCharacter

UCLASS(minimalapi)
class ASPGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	ASPGameMode();
    
    virtual void BeginPlay() override;
    
    UFUNCTION(BlueprintCallable, Category = "UMG Game")
    void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);
    
    void OnEnemyCreate(ASPEnemy *Enemy);
    void OnEnemyDead(ASPEnemy *Enemy);
    bool IsEnemyEmpty() const { return Enemies.Num() == 0; }
    int32 GetNumEnemy() const { return Enemies.Num(); }
    
    UFUNCTION(BlueprintCallable, Category = "UMG Game")
    void SetGamePause(bool Pause){ bGamePause = Pause; }
    bool IsGamePause() const{ return bGamePause; }
    
    UPROPERTY(EditAnywhere)
    ASPMapActor*    Map;
    
    UPROPERTY(EditAnywhere)
    float           Score;
   
    UPROPERTY()
    FBox2D          BoundingBox;
    
    // 视口大小
    FVector2D       ScreenSize;
    
protected:
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
    TSubclassOf<UUserWidget>    StartingWidgetClass;
    
    UPROPERTY()
    UUserWidget*                CurrentWidget;
    
    TArray<ASPEnemy*>           Enemies;
    
    bool        bGamePause;
};
