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

	/** interact_action Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	//UInputAction* Combat;
	UInputAction* Switch_weapon;

	


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
	// event tick
	virtual void Tick(float DeltaTime) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	//-----------------------------------------------------------------------------------------
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Weapon")
	UStaticMeshComponent* Weapon_mesh;
	//-----------------------------------------------------------------------------------------

	//sprinting boolean
	bool bIsSprinting = false;

	// Declare SprintSpeedMultiplier as a variable in the character class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprinting")
	float SprintSpeedMultiplier = 2.0f; // Example value, can be adjusted as needed
	
	//-----------------------------------------------------------------------------------------
	//demo exp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "demo exp")
	//TArray<class UAnimMontage*> demo_anim;
	UAnimMontage* demo_anim;

	UFUNCTION(BlueprintCallable, Category = "demo exp")
	void demo();
	//void demo(USkeletalMeshComponent* MeshComponent, UAnimInstance* demo_instance, UAnimMontage* MontageToPlay);

	UFUNCTION()
	void OndemoEnded(UAnimMontage* Montage, bool bInterrupted);
	
	UFUNCTION()
	//void note_begin(UAnimMontage* Montage);
	void note_begin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

	UFUNCTION()
	void note_end(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
	
	UFUNCTION(BlueprintCallable)
	void trace_hit();

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "demo exp")
	//class UAnimInstance* demo_instance;
	//--
	
	//-----------------------------------------------------------------------------------------

	// Declare dash properties
	
	//-----------------------------------------------------------------------------------------
	//combo_0
		/* basic anima instance to editor 
		UPROPERTY(EditAnywhere, Category = "Animation")
		class UAnimMontage* MyAnimationMontage;

		UPROPERTY()
		class UAnimInstance* MyAnimInstance;
		*/

		// infinete anima play 
		UPROPERTY(EditAnywhere, Category = "combo_0")
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
		
		
	//-----------------------------------------------------------------------------------------
	//combo_1
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "combo_1")
		UAnimMontage* slot1;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "combo_1")
		UAnimMontage* slot2;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "combo_1")
		UAnimMontage* slot3;
		
		int combo_count= 0;
		UFUNCTION(BlueprintCallable, Category = "combo_1")
		void combat();
		void combat_handle();
		void combat_reset();

		UFUNCTION()
		void combat_switcher(UAnimMontage* Montage, bool bInterrupted);
	//-----------------------------------------------------------------------------------------

		
		/* combo - 2
		// Player Anim Montages
		//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "combo_2")
		//UAnimMontage* m_pJumpMontage;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "combo_2")
		UAnimMontage* m_pLight_AttackMontage;

		UFUNCTION(BlueprintCallable)
		// Method for handling light attacks
		void LightAttack();
		// Method for getting whether player is attacking
		bool IsAttacking();
		int m_iComboAttackIndex = 0;

	// Event handler for montage notify begin
	UFUNCTION()
	void HandleOnMontageNotifyBegin(FName a_nNotifyName, const FBranchingPointNotifyPayload& a_pBranchingPayload);
	*/
	//-----------------------------------------------------------------------------------------
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		UStaticMeshComponent* cp_gun; 
	//-----------------------------------------------------------------------------------------
		UFUNCTION()
		void switch_weapon();

		// Array to hold references to all available weapons
		UPROPERTY(EditAnywhere, Category = "Weapons")
		TArray<AWeaponBase*> WeaponInventory;

		// Index of the currently equipped weapon
		int32 CurrentWeaponIndex;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "socket")
		USkeletalMeshSocket* back_socket;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Socket")
		FName SocketName;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Socket")
		FName BoneName;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Socket")
		FVector RelativeLocation;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Socket")
		FRotator RelativeRotation;
};

