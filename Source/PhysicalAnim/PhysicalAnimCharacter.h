// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PhysicalAnimCharacter.generated.h"

UCLASS(config=Game)
class APhysicalAnimCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	APhysicalAnimCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PhysicsAnimation, meta = (AllowPrivateAccess = "true"))
	class UPhysicalAnimationComponent* PhysicsAnimation;

protected:

	float FootInterpSpeed = 13.0f;
	float HipInterpSpeed = 7.0f;
	float TraceDistance = 55.0f;
	float AdjustOffset = 2.0f;
	float CapsuleHalfHeight;
	float LeftFootOffset;
	float RightFootOffset;

	FName LeftFootSocket = FName("foot_lSocket");
	FName RightFootSocket = FName("foot_rSocket");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = IK)
	float LeftEffectorLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = IK)
	float RightEffectorLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = IK)
	FRotator LeftFootRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = IK)
	FRotator RightFootRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = IK)
	float HipOffset;

	void UpdateIK(float DeltaTime);

	void TraceFoot(FName SocketName, float& OutOffset, FRotator& OutRotation, float DeltaTime);

	void UpdateHip(float DeltaTime);

	void UpdateFootEffector(float& OutEffectorLocation, float FootOffset, float DeltaTime);

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

