// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SpaceShoot.h"
#include "SPCharacter.h"
#include "SPPlayer.h"
#include "SPGameMode.h"

//////////////////////////////////////////////////////////////////////////
// ASPCharacter

ASPCharacter::ASPCharacter()
: StartPosition(0.0f, 0.0f, 370.0f)
{
    FVector2D ScreenSize(600, 740);
    ASPGameMode *GameMode = Cast<ASPGameMode>(UGameplayStatics::GetGameMode(this));
    if(GameMode)
    {
        ScreenSize = GameMode->ScreenSize;
    }
    
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    RootComponent = CameraComponent;
    
    //CameraComponent->AttachParent = RootComponent;
    CameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
    CameraComponent->OrthoWidth = ScreenSize.X;
    CameraComponent->OrthoNearClipPlane = 0.0f;
    CameraComponent->OrthoFarClipPlane = 1000.0f;
    CameraComponent->AspectRatio = ScreenSize.X / ScreenSize.Y;
    CameraComponent->bConstrainAspectRatio = true;
    CameraComponent->bAutoActivate = true;
    CameraComponent->bAutoRegister = true;
    CameraComponent->SetRelativeLocation(FVector(0, 100, ScreenSize.Y * 0.5f));
    CameraComponent->SetRelativeRotation(FRotator(0, -90, 0));
}

//////////////////////////////////////////////////////////////////////////
// Input

void ASPCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    PlayerActor = GetWorld()->SpawnActor<ASPPlayer>(StartPosition, FRotator(0.0f, 0.0f, 0.0f));
    if(PlayerActor != nullptr)
    {
        PlayerActor->Camp = ESPCamp::Attack;
        PlayerActor->bAttackable = true;
    }
}

void ASPCharacter::SetupPlayerInputComponent(class UInputComponent* InputCom)
{
    InputCom->BindAxis("MoveRight", this, &ASPCharacter::MoveRight);
    InputCom->BindAxis("MoveUp", this, &ASPCharacter::MoveUp);

    InputCom->BindTouch(IE_Pressed, this, &ASPCharacter::TouchStarted);
    InputCom->BindTouch(IE_Released, this, &ASPCharacter::TouchStopped);
}

void ASPCharacter::MoveRight(float Value)
{
    if(PlayerActor != nullptr)
    {
        PlayerActor->MoveRight(Value);
    }
}

void ASPCharacter::MoveUp(float Value)
{
    if(PlayerActor != nullptr)
    {
        PlayerActor->MoveUp(Value);
    }
}

void ASPCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
}

void ASPCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
}

