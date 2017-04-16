// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShoot.h"
#include "SPBullet.h"
#include "SPGameMode.h"
#include "SPBulletEvent.h"

ASPBullet::ASPBullet()
: LifeTime(5.0f)
{
    PrimaryActorTick.bCanEverTick = true;
    
    static ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> DefaultAsset(TEXT("/Game/SpaceShoot/Sprites/Bullet/1/am"));
    UPaperFlipbook *DefaultAm = DefaultAsset.Get();
    
    GetRenderComponent()->SetFlipbook(DefaultAm);
}

void ASPBullet::BeginPlay()
{
    Super::BeginPlay();

    for(auto iter = Events.CreateIterator(); iter; ++iter)
    {
        (*iter)->OnBeginPlay();
    }
}

void ASPBullet::Tick(float Delta)
{
    ASPEntity::Tick(Delta);
    
    ASPGameMode *GameMode = Cast<ASPGameMode>(UGameplayStatics::GetGameMode(this));
    if(nullptr == GameMode || GameMode->IsGamePause())
    {
        return;
    }
    if (nullptr == RootComponent)
    {
        return;
    }
    
    FVector Position = GetActorLocation();
    if(!GameMode->BoundingBox.IsInside(FVector2D(Position.X, Position.Z)))
    {
        Destroy();
        return;
    }
    
    Elapse += Delta;
    if(Elapse >= LifeTime)
    {
        Destroy();
        return;
    }

    for(auto iter = Events.CreateIterator(); iter; ++iter)
    {
        (*iter)->OnTick(Delta);
    }

    if (!FMath::IsNearlyZero(MotionInfo.Accelerate))
    {
        MotionInfo.MoveSpeed += MotionInfo.Accelerate * Delta;
    }
    if (!FMath::IsNearlyZero(MotionInfo.TangentAccelerate))
    {
        MotionInfo.TangentMoveSpeed += MotionInfo.TangentAccelerate * Delta;
    }
    if (!FMath::IsNearlyZero(MotionInfo.AngleAccelerate))
    {
        MotionInfo.AngleSpeed += MotionInfo.AngleAccelerate * Delta;
    }
    
    FQuat Rotation = GetActorQuat();
    if (!FMath::IsNearlyZero(MotionInfo.AngleSpeed))
    {
        // ÑØ×Å-YÖáÐý×ª¡£
        float Radian = FMath::DegreesToRadians(MotionInfo.AngleSpeed * Delta);
        Rotation *= FQuat(FVector(0.0f, -1.0f, 0.0f), Radian);
    }

    Position = FVector::ZeroVector;
    if (!FMath::IsNearlyZero(MoveSpeed))
    {
        Position += GetActorUpVector() * (Delta * MotionInfo.MoveSpeed);
    }
    if (!FMath::IsNearlyZero(MotionInfo.TangentMoveSpeed))
    {
        Position += GetActorForwardVector() * (Delta * MotionInfo.TangentMoveSpeed);
    }

    RootComponent->MoveComponent(Position, Rotation, false);
}

void ASPBullet::NotifyActorBeginOverlap(AActor* Other)
{
    Super::NotifyActorBeginOverlap(Other);
    
    ASPEntity *Entity = Cast<ASPEntity>(Other);
    if(Entity != nullptr && CanIAttack(Entity))
    {
        int32 DeltaHP = FMath::Max(Attack - Entity->Defence, 1);
        Entity->Damage(DeltaHP, this);
        
        bDead = true;
        Destroy();
    }
}

void ASPBullet::AddBulletEvent(USPBulletEvent *E)
{
    Events.Add(E);
    E->Owner = this;
}

void ASPBullet::RemoveBulletEvent(USPBulletEvent *E)
{
    Events.Remove(E);
    E->Owner = nullptr;
}
