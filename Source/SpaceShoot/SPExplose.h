// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SPEntity.h"
#include "SPExplose.generated.h"

class UAudioComponent;

/**
 * 
 */
UCLASS()
class SPACESHOOT_API ASPExplose : public ASPEntity
{
	GENERATED_BODY()
	
public:
    
    ASPExplose();
	
    UFUNCTION()
    void OnAnimationFinished();
    
    UFUNCTION()
    void OnSoundFinished();
    
    void TryDestroy();
    
private:
    
    UPROPERTY()
    UAudioComponent *AudioComponent;
    
    bool    bSoundEnd;
    bool    bAnimationEnd;
};
