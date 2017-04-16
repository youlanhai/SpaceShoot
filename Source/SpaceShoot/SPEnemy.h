// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SPCombat.h"
#include "SPEnemy.generated.h"

class ASPLevelActor;
class USPBulletEmitter;
class AAIController;

struct FEnemyDataRow;

/**
 * 
 */
UCLASS()
class SPACESHOOT_API ASPEnemy : public ASPCombat
{
	GENERATED_BODY()
public:
    ASPEnemy();
    
    bool Init(int32 ID, FEnemyDataRow *Data, ASPLevelActor *Level);
    
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void Tick(float Elapse) override;

    void SetAIControllerClass(TSubclassOf<AAIController> Class);

public:
    UPROPERTY()
    int32           ID;
    FEnemyDataRow*  Data;
    ASPLevelActor*  Level;
};
