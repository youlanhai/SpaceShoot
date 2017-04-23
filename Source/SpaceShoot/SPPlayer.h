// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SPCombat.h"
#include "SPPlayer.generated.h"

class USPBulletEmitter;

/**
 * 
 */
UCLASS()
class SPACESHOOT_API ASPPlayer : public ASPCombat
{
	GENERATED_BODY()
	
public:
    ASPPlayer();
    ~ASPPlayer();
	
    virtual void BeginPlay() override;
    virtual void Tick(float Elapse) override;
    
    void MoveRight(float Delta);
    void MoveUp(float Delta);
    
    void LimitInBoundary();
};
