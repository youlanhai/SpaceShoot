// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperFlipbookComponent.h"
#include "SPTypes.h"
#include "SPEntity.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOT_API ASPEntity : public APawn
{
	GENERATED_BODY()
public:
    ASPEntity();
   

    // End of AActor interface
    
    /** Returns RenderComponent subobject **/
    FORCEINLINE class UPaperFlipbookComponent* GetRenderComponent() const { return RenderComponent; }
    
    //virtual void NotifyActorBeginOverlap(AActor* Other) override;
    
    virtual bool CanIAttack(ASPEntity *Target);
    
    virtual void Damage(int32 DeltaHP, ASPEntity *Src);
    
    virtual void OnDead();
    
    void SetAnimation(const FString &Path);
    
public:
	
    UPROPERTY(EditAnywhere)
    int32   Hp;
    
    UPROPERTY(EditAnywhere)
    int32   HpMax;
    
    UPROPERTY(EditAnywhere)
    int32   Attack;
    
    UPROPERTY(EditAnywhere)
    int32   Defence;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float   MoveSpeed;
    
    UPROPERTY(EditAnywhere)
    ESPCamp Camp;
    
    UPROPERTY(EditAnywhere)
    bool    bAttackable; // 是否可被攻击
    
    bool    bDead;
    
protected:
    
    UPROPERTY(Category=Sprite, VisibleAnywhere, BlueprintReadOnly, meta=(ExposeFunctionCategories="Sprite,Rendering,Physics,Components|Flipbook", AllowPrivateAccess="true"))
    class UPaperFlipbookComponent* RenderComponent;
};
