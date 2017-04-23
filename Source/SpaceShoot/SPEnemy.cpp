// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShoot.h"
#include "SPEnemy.h"
#include "Engine.h"
#include "SPBullet.h"
#include "SPLevelActor.h"
#include "SPGameMode.h"
#include "SPBulletEmitter.h"
#include "SPGameInstance.h"
#include "EnemyDataRow.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "AIController.h"


ASPEnemy::ASPEnemy()
{
    PrimaryActorTick.bCanEverTick = true;
    UE_LOG(LogGame, Log, TEXT("Enemy Contruction"));
}

bool ASPEnemy::Init(int32 _ID, FEnemyDataRow *_Data, ASPLevelActor *_Level)
{
    this->ID = _ID;
    this->Data = _Data;
    this->Level = _Level;
    
    GetRenderComponent()->SetFlipbook(Data->Animation);
    
    Hp = Data->HPMax;
    Attack = Data->Attack;
    Defence = Data->Defence;
    MoveSpeed = Data->MoveSpeed;
    
    float AmRotation = Data->AmRotation;
    FRotator Rotation = RenderComponent->RelativeRotation;
    Rotation.Pitch += AmRotation;
    RenderComponent->SetRelativeRotation(Rotation);
    
    SetAIControllerClass(Data->ControllerClass);
    SwitchEmitter(Data->EmitterID);
    return true;
}

void ASPEnemy::BeginPlay()
{
    Super::BeginPlay();

    ASPGameMode *GameMode = Cast<ASPGameMode>(UGameplayStatics::GetGameMode(this));
    if (GameMode != nullptr)
    {
        GameMode->OnEnemyCreate(this);
    }
}

void ASPEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    ASPGameMode *GameMode = Cast<ASPGameMode>(UGameplayStatics::GetGameMode(this));
    if(GameMode != nullptr)
    {
        GameMode->OnEnemyDead(this);
    }
    
    StopFire();
    
    Super::EndPlay(EndPlayReason);
}

void ASPEnemy::Tick(float Elapse)
{
    ASPCombat::Tick(Elapse);

    ASPGameMode *GameMode = Cast<ASPGameMode>(UGameplayStatics::GetGameMode(this));
    if (nullptr == GameMode || GameMode->IsGamePause())
    {
        return;
    }

    FVector Position = GetActorLocation();
    if (Position.X < GameMode->BoundingBox.Min.X ||
        Position.X > GameMode->BoundingBox.Max.X ||
        Position.Z < GameMode->BoundingBox.Min.Y)
    {
        Destroy();
        return;
    }
}

void ASPEnemy::SetAIControllerClass(TSubclassOf<AAIController> Class)
{
    if (Class == nullptr)
    {
        return;
    }

    AAIController *Ctl = Cast<AAIController>(GetWorld()->SpawnActor(Class));
    if (Ctl == nullptr)
    {
        return;
    }

    Ctl->Possess(this);
}
