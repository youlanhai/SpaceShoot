// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/Pawn.h"
#include "SPCharacter.generated.h"

// This class is the default character for SpaceShoot, and it is responsible for all
// physical interaction between the player and the world.
//
//   The capsule component (inherited from ACharacter) handles collision with the world
//   The CharacterMovementComponent (inherited from ACharacter) handles movement of the collision capsule
//   The Sprite component (inherited from APaperCharacter) handles the visuals

class ASPPlayer;

UCLASS(config=Game)
class ASPCharacter : public APawn
{
	GENERATED_BODY()

    UPROPERTY()
    class ASPPlayer*    PlayerActor;
    
    UPROPERTY(EditAnywhere)
    FVector     StartPosition;
    
    UPROPERTY(EditAnywhere)
    UCameraComponent*   CameraComponent;
    
protected:

	/** Called for side to side input */
	void MoveRight(float Value);
	void MoveUp(float Value);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

public:

	ASPCharacter();
    
    virtual void BeginPlay() override;
    
};
