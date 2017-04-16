// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "smartjson.hpp"
#include "SPLevelActor.generated.h"

class AAIController;
class ASPGameMode;

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

    void BeginNextWave(ASPGameMode *GameMode);
    
private:
    TArray<int32>   WaveIDs;
    
    UPROPERTY()
    int32           CurrentWaveIndex;
    
    UPROPERTY()
    int32           NumEnemies;

    UPROPERTY()
    UDataTable*     EnemyDataTable;

    UPROPERTY()
    UDataTable*     LevelDataTable;

    TMap<int32, TArray<FLevelDataRow*>>     WaveDataMap;
};
