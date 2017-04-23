// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShoot.h"
#include "SPCombat.h"
#include "SPGameMode.h"
#include "SPGameInstance.h"
#include "SPBulletEmitter.h"


ASPCombat::ASPCombat()
{

}


void ASPCombat::Tick(float Elapse)
{
    ASPEntity::Tick(Elapse);

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

    TickMove(Elapse);
}

void ASPCombat::StartFire()
{
    bFiring = true;
    if (Emitter != nullptr)
    {
        Emitter->Start();
    }
}

void ASPCombat::StopFire()
{
    bFiring = false;
    if (Emitter != nullptr)
    {
        Emitter->Stop();
    }
}

void ASPCombat::SwitchEmitter(int32 EmitterID)
{
    if (Emitter != nullptr)
    {
        Emitter->Stop();
        Emitter = nullptr;
    }

    TSubclassOf<USPBulletEmitter> *EmitterClass = Cast<USPGameInstance>(GetGameInstance())->EmitterClasses.Find(EmitterID);
    if (EmitterClass == nullptr)
    {
        return;
    }

    Emitter = static_cast<USPBulletEmitter*>(StaticConstructObject_Internal(*EmitterClass));
    Emitter->Init(this, EmitterID);

    if (bFiring)
    {
        Emitter->Start();
    }
}

void ASPCombat::MoveToDirect(const FVector &Destination)
{
    Path.Empty();
    Path.Add(GetActorLocation());
    Path.Add(Destination);

    PathIndex = 0;
    MoveElapse = 0.0f;
}

void ASPCombat::TickMove(float Elapse)
{
    if (Path.Num() == 0)
    {
        return;
    }

    MoveElapse += Elapse;
    if (PathIndex + 1 < Path.Num())
    {
        FVector Position;
        FVector Dir = Path[PathIndex + 1] - Path[PathIndex];

        float TotalTime = Dir.Size() / MoveSpeed;
        if (MoveElapse >= TotalTime)
        {
            MoveElapse = 0.0f;
            ++PathIndex;
            Position = Path[PathIndex];
        }
        else
        {
            Position = Path[PathIndex] + Dir * (MoveElapse / TotalTime);
        }

        SetActorLocation(Position);
    }
    else
    {
        Path.Empty();
        OnMoveToFinished.Broadcast();
    }
}
