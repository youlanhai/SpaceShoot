// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShoot.h"
#include "SPBulletEmitter.h"
#include "SPEntity.h"
#include "SPBullet.h"
#include "TimerManager.h"
#include "SPGameMode.h"
#include "EmitterDataRow.h"
#include "EngineUtils.h"

#include <PaperFlipbook.h>

USPBulletEmitter::USPBulletEmitter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, Owner_(nullptr)
, ID_(0)
, bPause_(true)
, bLoop_(true)
, TickIndex_(0)
{
    //static ConstructorHelpers::FObjectFinderOptional<UDataTable> Asset(TEXT("/Game/SpaceShoot/Data/Emitter"));
    //if (Asset.Succeeded())
    //{
    //    Table = Asset.Get();
    //}

    BulletLife = 5.0f;
    BulletCount = 1;
    BulletIDs.Add(1);
    InnerInterval = 0.5f;

}

USPBulletEmitter::~USPBulletEmitter()
{

}

bool USPBulletEmitter::Init(ASPEntity *Owner, int32 ID)
{
    Owner_ = Owner;
    ID_ = ID;
    //if(Table == nullptr)
    //{
    //    return false;
    //}

    //Data_ = Table->FindRow<FEmitterDataRow>(*FString::FromInt(ID), TEXT("Message For Load"));
    //if(Data_ == nullptr)
    //{
    //    return false;
    //}
    return true;
}

void USPBulletEmitter::Start()
{
    bPause_ = false;
    if(Owner_)
    {
        Owner_->GetWorldTimerManager().SetTimer(TimerHandle_, this, &USPBulletEmitter::OnTimerEmit, 0.01f, false);
    }
}

void USPBulletEmitter::Stop()
{
    bPause_ = true;
    if(Owner_ && TimerHandle_.IsValid())
    {
        Owner_->GetWorldTimerManager().ClearTimer(TimerHandle_);
        TimerHandle_.Invalidate();
    }
}

void USPBulletEmitter::OnTimerEmit()
{
    TimerHandle_.Invalidate();
    
    if(bPause_)
    {
        return;
    }
    
    float Delay = InnerInterval;
    if(FMath::IsNearlyZero(Delay))
    {
        for (; TickIndex_ < BulletCount; ++TickIndex_)
        {
            Emit();
        }
    }
    else
    {
        Emit();
        ++TickIndex_;
    }
    
    if(TickIndex_ >= BulletCount)
    {
        if(!bLoop_)
        {
            Stop();
            OnFinished.ExecuteIfBound();
            return;
        }
        else
        {
            TickIndex_ = 0;
            Delay += OuterInterval;
        }
    }
    
    Delay = FMath::Max(Delay, 0.001f);
    Owner_->GetWorldTimerManager().SetTimer(TimerHandle_, this, &USPBulletEmitter::OnTimerEmit, Delay, false);
}

void USPBulletEmitter::Emit()
{
    ASPGameMode *GameMode = Cast<ASPGameMode>(UGameplayStatics::GetGameMode(Owner_));
    if(nullptr == GameMode || GameMode->IsGamePause())
    {
        return;
    }

    int32 nBullets = BulletIDs.Num();
    if (nBullets <= 0)
    {
        return;
    }
    
    int32 BulletID = BulletIDs[TickIndex_ % nBullets];
    
    FRotator Rotation = Owner_->GetActorRotation();
    Rotation.Pitch += AngleOffset * TickIndex_;
    
    FVector Position = Owner_->GetActorLocation() + Position_ + PosOffset * TickIndex_;
    
    ASPBullet *Bullet = Owner_->GetWorld()->SpawnActor<ASPBullet>(Position, Rotation);
    if(Bullet != nullptr)
    {
        UPaperFlipbook *FlipBook = LoadObject<UPaperFlipbook>(nullptr, TEXT("/Game/SpaceShoot/Sprites/Bullet/2/am"));
        if(FlipBook != nullptr)
        {
            Bullet->GetRenderComponent()->SetFlipbook(FlipBook);
        }

        Bullet->Camp = Owner_->Camp;
        Bullet->Index = TickIndex_;
        Bullet->LifeTime = BulletLife;
        Bullet->MotionInfo = BulletMotionInfo;

        OnBulletSpawned(Bullet);
    }
}
