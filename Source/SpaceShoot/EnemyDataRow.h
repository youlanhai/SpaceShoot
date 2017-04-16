// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/DataTable.h"
#include "EnemyDataRow.generated.h"

/**
 * 
 */
USTRUCT()
struct SPACESHOOT_API FEnemyDataRow : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()
public:
    FEnemyDataRow();

    UPROPERTY(EditAnywhere)
    FText   Name;

    UPROPERTY(EditAnywhere)
    FString Describe;

    // 最大血量
    UPROPERTY(EditAnywhere)
    int32   HPMax;

    // 攻击力
    UPROPERTY(EditAnywhere)
    int32   Attack;

    // 防御力
    UPROPERTY(EditAnywhere)
    int32   Defence;

    // 移动速度
    UPROPERTY(EditAnywhere)
    float   MoveSpeed;

    // 动画
    UPROPERTY(EditAnywhere)
    class UPaperFlipbook*     Animation;

    // 动画偏转角度
    UPROPERTY(EditAnywhere)
    float   AmRotation;

    // 发射器ID
    UPROPERTY(EditAnywhere)
    int32   EmitterID;

    // AI控制器类
    UPROPERTY(EditAnywhere)
    TSubclassOf<class AAIController>    ControllerClass;
};
