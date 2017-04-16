// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShoot.h"
#include "SPMapActor.h"
#include "SPGameMode.h"

ASPMapActor::ASPMapActor()
: ScrollSpeed(50.0f)
, TotalHeight(0.0f)
{
    PrimaryActorTick.bCanEverTick = true;
    
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    
    ASPGameMode *GameMode = Cast<ASPGameMode>(UGameplayStatics::GetGameMode(this));
    if(GameMode)
    {
        ScreenBox = GameMode->BoundingBox;
    }
}

void ASPMapActor::Tick(float Elapse)
{
    Super::Tick(Elapse);
    
    if(Sprites.Num() == 0)
    {
        return;
    }
    
    /**
     *  最大的Z = ScreenBox.Min.Y;
     *  最小的Z = ScreenBox.Max.Y - TotalHeight;
     *  滚动方向：最大Z -> 最小Z，然后再移到最大Z。
     */
    
    float MaxZ = ScreenBox.Min.Y;
    float MinZ = ScreenBox.Max.Y - TotalHeight;
    
    FVector Position = GetActorLocation();
    Position.Z -= Elapse * ScrollSpeed;
    if(Position.Z <= MinZ)
    {
        float OverFlow = MinZ - Position.Z;
        Position.Z = MaxZ - OverFlow;
    }
    SetActorLocation(Position);
}

void ASPMapActor::InitMap(const FString &Image)
{
    UPaperSprite *Sprite = LoadObject<UPaperSprite>(nullptr, *Image);
    if(Sprite == nullptr)
    {
        return;
    }
    
    for(int i = 0; i < Sprites.Num(); ++i)
    {
        Sprites[i]->DestroyComponent();
    }
    Sprites.Empty();

    FVector2D Size = Sprite->GetSourceSize();
    int NComs = FMath::CeilToInt(ScreenBox.GetSize().Y / Size.Y) + 1;
    TotalHeight = NComs * Size.Y;
    
    UE_LOG(LogGame, Log, TEXT("Sprite Size: %s, Num Components: %d, TotalHeight: %0.3f"),
           *Size.ToString(), NComs, TotalHeight);
    
    for(int i = 0; i < NComs; ++i)
    {
        FString Name = FString::Printf(TEXT("MapSpriteComponent_%d"), i);
        UPaperSpriteComponent *Com = NewObject<UPaperSpriteComponent>(this, *Name);
        Com->RegisterComponent();
        Com->SetRelativeLocation(FVector(0, 0, i * Size.Y));
        Com->SetSprite(Sprite);
        Com->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        Com->Mobility = EComponentMobility::Movable;
        Com->AttachTo(RootComponent);
        
        Sprites.Push(Com);
    }
}
