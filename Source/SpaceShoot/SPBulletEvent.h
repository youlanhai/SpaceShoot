// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "SPBulletEvent.generated.h"

class ASPBullet;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class SPACESHOOT_API USPBulletEvent : public UObject
{
public:
	GENERATED_BODY()
	
public:
    USPBulletEvent();
	
    UFUNCTION(BlueprintImplementableEvent)
    void OnBeginPlay();

    UFUNCTION(BlueprintImplementableEvent)
    void OnTick(float Delta);
	

    UPROPERTY(BlueprintReadOnly)
    ASPBullet*      Owner;
};
