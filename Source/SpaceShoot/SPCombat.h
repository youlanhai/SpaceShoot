// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SPEntity.h"
#include "SPCombat.generated.h"

class ASPLevelActor;
class USPBulletEmitter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEntityMoveFinishedDelegate);

/**
 * 
 */
UCLASS()
class SPACESHOOT_API ASPCombat : public ASPEntity
{
	GENERATED_BODY()
public:
    ASPCombat();

    void Tick(float Elapse) override;

    UFUNCTION(BlueprintCallable, Category = "Enemy")
    void StartFire();

    UFUNCTION(BlueprintCallable, Category = "Enemy")
    void StopFire();

    // 切换发射器
    UFUNCTION(BlueprintCallable, Category = "Enemy")
    void SwitchEmitter(int32 EmitterID);

    // 执行移动到目标点
    UFUNCTION(BlueprintCallable, Category = "Enemy")
    void MoveToDirect(const FVector &Destination);

    // 移动结束回调
    UPROPERTY(BlueprintAssignable)
    FEntityMoveFinishedDelegate OnMoveToFinished;

protected:
    void TickMove(float Elapse);

    // 移动路点
    TArray<FVector> Path;

    // 路点索引
    int32           PathIndex;

    // 已经移动的时间
    float           MoveElapse;

    // 发射器
    UPROPERTY()
    USPBulletEmitter*   Emitter;

    // 是否正在开火中
    bool            bFiring;
};
