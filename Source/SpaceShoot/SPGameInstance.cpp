// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShoot.h"
#include "SPGameInstance.h"
#include "SPBulletEmitter.h"
#include "EngineUtils.h"

void USPGameInstance::Init()
{
    Super::Init();

    UE_LOG(LogGame, Log, TEXT("USPGameInstance Init"));

    TArray<UObject*> Classes;
    if (EngineUtils::FindOrLoadAssetsByPath(TEXT("/Game/SpaceShoot/Blueprint/Emitter"), Classes, EngineUtils::ATL_Class))
    {
        for (auto iter = Classes.CreateIterator(); iter; ++iter)
        {
            FString Name = (*iter)->GetFName().ToString();
            UE_LOG(LogGame, Log, TEXT("Load Emitter Class '%s'"), *Name);

            if (Name.StartsWith(TEXT("Emitter_")))
            {
                int32 ID = 0;
                for (int32 i = 8; i < Name.Len(); ++i)
                {
                    TCHAR ch = Name[i];
                    if (!FChar::IsDigit(ch))
                    {
                        break;
                    }
                    ID = ID * 10 + ch - '0';
                }

                EmitterClasses.Add(ID, static_cast<UClass*>(*iter));
                UE_LOG(LogGame, Log, TEXT("Load Emitter Class %d: '%s'"), ID, *Name);
            }
        }
    }
}

