// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShoot.h"
#include "SPLevelActor.h"
#include "SPGameMode.h"
#include "SPEnemy.h"
#include "SPMapActor.h"
#include "AIController.h"
#include "EnemyDataRow.h"
#include "LevelDataRow.h"

// Sets default values
ASPLevelActor::ASPLevelActor()
: CurrentWaveIndex(-1)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    static ConstructorHelpers::FObjectFinderOptional<UDataTable> EnemyDataTableAsset(TEXT("/Game/SpaceShoot/Data/EnemyData"));
    if (EnemyDataTableAsset.Succeeded())
    {
        EnemyDataTable = EnemyDataTableAsset.Get();
    }

    static ConstructorHelpers::FObjectFinderOptional<UDataTable> LevelDataTableAsset(TEXT("DataTable'/Game/SpaceShoot/Data/LevelData1.LevelData1'"));
    if (LevelDataTableAsset.Succeeded())
    {
        LevelDataTable = LevelDataTableAsset.Get();

        for (auto it = LevelDataTable->RowMap.CreateConstIterator(); it; ++it)
        {
            FLevelDataRow *Row = reinterpret_cast<FLevelDataRow*>(it.Value());
            auto &Arr = WaveDataMap.FindOrAdd(Row->WaveID);
            Arr.Add(Row);
        }

        WaveIDs.Empty();
        WaveDataMap.GetKeys(WaveIDs);
    }
    UE_LOG(LogGame, Log, TEXT("Num Actions %d"), WaveIDs.Num());
}

// Called when the game starts or when spawned
void ASPLevelActor::BeginPlay()
{
	Super::BeginPlay();
    
    ASPMapActor *Map = GetWorld()->SpawnActor<ASPMapActor>(FVector(0, -10, 0), FRotator());
    if(Map != nullptr)
    {
        Map->InitMap(TEXT("/Game/SpaceShoot/Sprites/Map/bg_hei_0_Sprite"));
    }
}

// Called every frame
void ASPLevelActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
    
    ASPGameMode *GameMode = Cast<ASPGameMode>(UGameplayStatics::GetGameMode(this));
    if(nullptr == GameMode || GameMode->IsGamePause())
    {
        return;
    }
    
    NumEnemies = GameMode->GetNumEnemy();
    if(NumEnemies == 0)
    {
        BeginNextWave(GameMode);
    }
}

void ASPLevelActor::BeginNextWave(ASPGameMode *GameMode)
{
    if(WaveIDs.Num() == 0)
    {
        return;
    }
    
    if(CurrentWaveIndex + 1 >= WaveIDs.Num())
    {
        // TODO 处理游戏结束事件
        CurrentWaveIndex = -1;
    }
    
    CurrentWaveIndex += 1;
    UE_LOG(LogGame, Log, TEXT("Begin Next Wave %d"), CurrentWaveIndex);
    
    int32 WaveID = WaveIDs[CurrentWaveIndex];
    
    TArray<FLevelDataRow*> &WaveData = WaveDataMap[WaveID];
    for(auto LevelRow : WaveData)
    {
        int32 PlaneID = LevelRow->EntityID;

        FVector Position = GetActorLocation();
        Position.X = 0;
        Position.Z = GameMode->BoundingBox.Max.Y;
        Position += LevelRow->Position;

        FName Key = *FString::FromInt(PlaneID);
        FEnemyDataRow *DataRow = EnemyDataTable->FindRow<FEnemyDataRow>(Key, TEXT("Level Actor"));
        if (DataRow == nullptr)
        {
            continue;
        }

        ASPEnemy *Enemy = GetWorld()->SpawnActor<ASPEnemy>(Position, FRotator(180.0f, 0.0f, 0.0f));
        if (Enemy != nullptr)
        {
            Enemy->Init(PlaneID, DataRow, this);
            Enemy->Camp = LevelRow->Camp;
            Enemy->bAttackable = true;
        }
    }
}
