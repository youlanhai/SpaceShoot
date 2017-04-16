// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "SPMapActor.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOT_API ASPMapActor : public AActor
{
	GENERATED_BODY()
public:
    ASPMapActor();
    
    virtual void Tick(float Elapse) override;
	
	UPROPERTY(EditAnywhere)
    float   ScrollSpeed;
    
    void InitMap(const FString &Image);
    
protected:
    FBox2D      ScreenBox;
    float       TotalHeight;
    
    TArray<UPaperSpriteComponent*> Sprites;
};
