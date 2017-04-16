// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShoot.h"
#include "SPEntity.h"
#include "SPExplose.h"

void OnExploseEnd(AActor *Actor)
{
    Actor->Destroy();
}

ASPEntity::ASPEntity()
: Hp(1000)
, HpMax(1000)
, Attack(100)
, Defence(0)
, MoveSpeed(50.0f)
, Camp(ESPCamp::Peace)
, bAttackable(false)
, bDead(false)
{
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    
    RenderComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("RenderComponent"));
    RenderComponent->AttachTo(RootComponent);
    //RenderComponent->AttachParent = RootComponent;
    RenderComponent->SetCollisionProfileName(TEXT("OverlapAll"));
    RenderComponent->Mobility = EComponentMobility::Movable;
    RenderComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    RenderComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    RenderComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
}

//void ASPEntity::NotifyActorBeginOverlap(AActor* Other)
//{
//    Super::NotifyActorBeginOverlap(Other);
//    
//    UE_LOG(LogGame, Log, TEXT("Overlap: %s and %s"), *GetName(), *Other->GetName());
//}

bool ASPEntity::CanIAttack(ASPEntity *Target)
{
    if(!Target || bDead || Target->bDead || !Target->bAttackable)
        return false;
    
    if(IsRelationBad(Camp, Target->Camp))
        return true;
    
    return false;
}

void ASPEntity::Damage(int32 DeltaHP, ASPEntity *Src)
{
    Hp = FMath::Clamp(Hp - DeltaHP, 0, HpMax);
    if(Hp == 0)
    {
        bDead = true;
        OnDead();
    }
}

void ASPEntity::OnDead()
{
    ASPExplose *Actor = GetWorld()->SpawnActor<ASPExplose>(GetActorLocation(), FRotator(0, 0, 0));
    if(Actor != nullptr)
    {
        Actor->SetAnimation(TEXT("/Game/SpaceShoot/Sprites/Explose/1/am"));
    }
    
    Destroy();
}

void ASPEntity::SetAnimation(const FString &Path)
{
    UPaperFlipbook *FlipBook = LoadObject<UPaperFlipbook>(nullptr, *Path);
    if(FlipBook != nullptr)
    {
        GetRenderComponent()->SetFlipbook(FlipBook);
    }
}
