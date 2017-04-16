// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataAsset.h"
#include "SPBulletEmitter.h"
#include "MyDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOT_API UMyDataAsset : public UDataAsset
{
public:
    GENERATED_BODY()

public:

    UPROPERTY(Category = MapsAndSets, EditAnywhere)
    TMap<int32, FString> Emitters;
	
    UPROPERTY(EditAnywhere)
    TArray<TSubclassOf<USPBulletEmitter>> EmitterArray;

    UPROPERTY(EditAnywhere)
    int32   TestInt;
};
