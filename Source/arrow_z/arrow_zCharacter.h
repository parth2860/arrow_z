// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "arrow_zCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class Aarrow_zCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** interact_action Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Sprint_Action;

	/** dash Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DashAction;

	/** interact_action Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* Interact_Action;

	/** interact_action Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	//UInputAction* Combat;
	UInputAction* Combat_Action;

	


public:
	Aarrow_zCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for looking input */
	void Sprint(const FInputActionValue& Value);
	/** Called for looking input */
	void Sprint_release(const FInputActionValue& Value);

	/** Called for dash input */
	void Dash(const FInputActionValue& Value);

	/** Called for interact_action input */
	void Interact_action(const FInputActionValue& Value);

	/** Called for comabt input */
	void Combat(const FInputActionValue& Value);

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

	//sprinting boolean
	bool bIsSprinting = false;

	// Declare SprintSpeedMultiplier as a variable in the character class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprinting")
	float SprintSpeedMultiplier = 2.0f; // Example value, can be adjusted as needed

	// Declare dash properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
		float DashDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
		float DashCooldown;
		/* basic anima instance to editor 
		UPROPERTY(EditAnywhere, Category = "Animation")
		class UAnimMontage* MyAnimationMontage;

		UPROPERTY()
		class UAnimInstance* MyAnimInstance;
		*/

		// infinete anima play 
		UPROPERTY(EditAnywhere, Category = "Animation")
		TArray<class UAnimMontage*> ComboAttackMontages;

		UPROPERTY()
		class UAnimInstance* MyAnimInstance;

		int32 CurrentMontageIndex;
		// Declare a variable to track the number of clicks
		int32 NumClicks = 0;

		void PlayComboAttack();
		//void PlayNextComboMontage();
		void ResetNumClicks();
		// Function to trigger attacks
		UFUNCTION()
		void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
		//--
		
		/* 
		//-combo_1
		// Animation montage references

		// Combo - related variables
		int32 ComboCount;
		// Declare a variable to track the number of clicks
		int32 NumClicks = 0;
		bool bIsAttacking;

		void ResetNumClicks();
		// Function to trigger attacks
		void StartComboAttack();

		UPROPERTY(EditDefaultsOnly, Category = "Combat")
		UAnimMontage* Attack1Montage;

		UPROPERTY(EditDefaultsOnly, Category = "Combat")
		UAnimMontage* Attack2Montage;

		UPROPERTY(EditDefaultsOnly, Category = "Combat")
		UAnimMontage* Attack3Montage;

		// Function to handle combo logic
		//void HandleCombo();
		// Event called when an animation montage ends
		//UFUNCTION()
		//void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
		*/
		//--------------------------------------------
		
		/* combo-2
		// Player Anim Montages
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		UAnimMontage* m_pJumpMontage;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		UAnimMontage* m_pLight_AttackMontage;

		// Method for handling light attacks
		void LightAttack();
		// Method for getting whether player is attacking
		bool IsAttacking();
		int m_iComboAttackIndex = 0;

	// Event handler for montage notify begin
	UFUNCTION()
	void HandleOnMontageNotifyBegin(FName a_nNotifyName, const FBranchingPointNotifyPayload& a_pBranchingPayload);
	*/

};

