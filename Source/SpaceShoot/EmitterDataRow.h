// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <Engine/DataTable.h>

#include "EmitterDataRow.generated.h"

/**
 * 
 */
USTRUCT()
struct SPACESHOOT_API FEmitterDataRow : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()
public:
    FEmitterDataRow();

    UPROPERTY(EditAnywhere)
    FString     Describe;

    // 一组发射的子弹个数
    UPROPERTY(EditAnywhere)
    int32       BulletCount;

    // 子弹ID列表
    UPROPERTY(EditAnywhere)
    TArray<int32> BulletIDs;

    // 组内时间间隔，即子弹和子弹直接的时间间隔
    UPROPERTY(EditAnywhere)
    float       InnerInterval;

    // 组外时间间隔
    UPROPERTY(EditAnywhere)
    float       OuterInterval;

    // 位置偏移
    UPROPERTY(EditAnywhere)
    FVector     PosOffset;

    // 角度偏移
    UPROPERTY(EditAnywhere)
    float       AngleOffset;

    // 速度偏移
    UPROPERTY(EditAnywhere)
    float       SpeedOffset;

    // 是否可转向
    UPROPERTY(EditAnywhere)
    bool        Rotatable;
};
