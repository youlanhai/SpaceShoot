// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/DataTable.h"
#include "SPTypes.h"
#include "LevelDataRow.generated.h"

/**
 * 
 */
USTRUCT()
struct SPACESHOOT_API FLevelDataRow : public FTableRowBase
{
    GENERATED_BODY()
public:
    FLevelDataRow();

    // 波编号。同一波Entity会一起出现
    UPROPERTY(EditAnywhere)
    int32       WaveID;

    // 当前Entity在该波中，延迟出现的时间
    UPROPERTY(EditAnywhere)
    float       Delay;

    // Entity编号
    UPROPERTY(EditAnywhere)
    int32       EntityID;

    // Entity出现的偏移位置
    UPROPERTY(EditAnywhere)
    FVector     Position;

    // Entity的阵营
    UPROPERTY(EditAnywhere)
    ESPCamp     Camp;
};
