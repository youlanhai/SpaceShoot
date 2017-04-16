// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "SPMotionInfo.generated.h"

/**
 * 
 */
USTRUCT()
struct SPACESHOOT_API FSPMotionInfo
{
public:
    GENERATED_USTRUCT_BODY()

public:
    FSPMotionInfo();

    // 移动速度
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float       MoveSpeed;

    // 加速度
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float   Accelerate;

    // 切线速度
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float   TangentMoveSpeed;

    // 切线加速度
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float   TangentAccelerate;

    // 角速度
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float   AngleSpeed;

    // 角加速度
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float   AngleAccelerate;
};
