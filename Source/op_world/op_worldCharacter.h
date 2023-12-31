// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "op_worldCharacter.generated.h"


UCLASS(config=Game)
class Aop_worldCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** fire Action */
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	//class UInputAction* FireAction;
	//-----------------------------------------------------------------------------------------------
	// Hook mesh component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grappling Hook", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* GrapplingHook;

	// Collision component for the hook
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grappling Hook", meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent* CollisionComponent;

	// Declare a variable for the cable component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cable", meta = (AllowPrivateAccess = "true"))
		class UCableComponent* CableComponent;
	//-----------------------------------------------------------------------------------------------
	// Function to move the player forward
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void MoveForward(float Value);
	//-----------------------------------------------------------------------------------------------


public:
	Aop_worldCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	//void Fire(const FInputActionValue& Value);
	/** Called for looking input */
	void Fire();
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:
	// Function to perform line trace for shooting
	void PerformLineTrace();
	void Swing();
	void AGrapplingHook();
	void StartGrapplingHook();
	void StopGrapplingHook();
	void HandleGrapplingHook();
	void HandleCable();
	// Variables for line trace
	FVector TraceStart;
	FVector TraceEnd;
	float TraceDistance;
};

