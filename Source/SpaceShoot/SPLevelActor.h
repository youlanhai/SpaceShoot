// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SPLevelActor.generated.h"

class AAIController;
class ASPGameMode;
class ASPMapActor;

class UDataTable;

struct FLevelDataRow;

UCLASS()
class SPACESHOOT_API ASPLevelActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPLevelActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    // 加载关卡的数据。如果加载失败，返回false。
    UFUNCTION(BlueprintCallable, Category = "Level")
    bool LoadLevelData(int32 ID);

    void BeginNextWave(ASPGameMode *GameMode);
    
private:
    // 关卡数据ID
    int32           ID;

    // 当前关卡中的所有波编号。从小到大排列
    TArray<int32>   WaveIDs;
    
    // 当前波的索引
    UPROPERTY()
    int32           CurrentWaveIndex;
    
    // 当前存活的敌人数量。当数量为0的时候，会切换到下一波
    UPROPERTY()
    int32           NumEnemies;

    // 敌人数据表
    UPROPERTY()
    UDataTable*     EnemyDataTable;

    // 关卡数据表
    UPROPERTY()
    UDataTable*     LevelDataTable;

    // 背景滚动地图
    UPROPERTY()
    ASPMapActor*    Map;

    TMap<int32, TArray<FLevelDataRow*>>     WaveDataMap;
};
