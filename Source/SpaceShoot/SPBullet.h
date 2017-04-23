// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SPEntity.h"
#include "SPMotionInfo.h"
#include "SPBullet.generated.h"

class USPBulletEvent;

/**
 * 
 */
UCLASS()
class SPACESHOOT_API ASPBullet : public ASPEntity
{
	GENERATED_BODY()
public:
    ASPBullet();

    virtual void BeginPlay() override;
    
    virtual void Tick(float Elapse) override;
	
    virtual void NotifyActorBeginOverlap(AActor* Other) override;

    UFUNCTION(BlueprintCallable, Category = "Bullet")
    void AddBulletEvent(USPBulletEvent *E);

    UFUNCTION(BlueprintCallable, Category = "Bullet")
    void RemoveBulletEvent(USPBulletEvent *E);

public:
    // 生命周期
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float       LifeTime;

    // 已经运动过的时间。
    UPROPERTY(BlueprintReadOnly)
    float       Elapse;

    // 发射器发射出来的顺序索引
    UPROPERTY(BlueprintReadOnly)
    int32       Index;

    UPROPERTY(BlueprintReadWrite)
    FSPMotionInfo   MotionInfo;

protected:

    UPROPERTY()
    TArray<USPBulletEvent*> Events;
};
