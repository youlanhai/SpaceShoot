// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Object.h"
#include "SPMotionInfo.h"
#include "SPBulletEmitter.generated.h"

DECLARE_DELEGATE(FBulletEmitterFinishedDelegate);

class ASPEntity;
class ASPBullet;

UCLASS(BlueprintType, Blueprintable)
class SPACESHOOT_API USPBulletEmitter : public UObject
{
public:
	GENERATED_UCLASS_BODY()
public:
	virtual ~USPBulletEmitter();
    
    virtual bool Init(ASPEntity *Owner, int32 ID);

	virtual void Start();
	virtual void Stop();

    FBulletEmitterFinishedDelegate OnFinished;

    UFUNCTION(BlueprintImplementableEvent)
    void OnBulletSpawned(ASPBullet *Bullet);

public:
    // 子弹生命
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float       BulletLife;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString     Describe;

    // 一组发射的子弹个数
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32       BulletCount;

    // 子弹ID列表
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<int32> BulletIDs;

    // 组内时间间隔，即子弹和子弹直接的时间间隔
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float       InnerInterval;

    // 组外时间间隔
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float       OuterInterval;

    // 位置偏移
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector     PosOffset;

    // 角度偏移
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float       AngleOffset;

    // 速度偏移
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float       SpeedOffset;

    // 是否可转向
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool        Rotatable;

    // 子弹初始运动参数
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FSPMotionInfo   BulletMotionInfo;

protected:
	void OnTimerEmit();
    
	virtual void Emit();
    
    ASPEntity*          Owner_;
    int32               ID_;
    FTimerHandle        TimerHandle_;
    
    bool                bPause_;
    bool                bLoop_;
    int32               TickIndex_;
    FVector             Position_;
};
