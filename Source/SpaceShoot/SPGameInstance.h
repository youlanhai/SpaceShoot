// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "SPGameInstance.generated.h"

class USPBulletEmitter;

/**
 * 
 */
UCLASS()
class SPACESHOOT_API USPGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	
    virtual void Init() override;
	
    UPROPERTY()
    TMap<int32, TSubclassOf<USPBulletEmitter>> EmitterClasses;
};
