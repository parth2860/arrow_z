// Copyright Epic Games, Inc. All Rights Reserved.

#include "arrow_zCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "DrawDebugHelpers.h" // Include for visual debugging
#include "cp_interect.h"//spawned actor
#include "LightSwitchBoth.h"//spawned actor

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// Aarrow_zCharacter

Aarrow_zCharacter::Aarrow_zCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//--------------------------------------------------------------------------------------------------------------


    //--------------------------------------------------------------------------------------------------------------
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	// Initialize variables
	//ComboCount = 0;
	//bIsAttacking = false;

	//Attack1Montage = LoadObject<UAnimMontage>(nullptr, TEXT("D:/Users/PARTH/Documents/Unreal Projects/c++/arrow_z/Content/assets/animation/Attack1_Montage.uasset"));
	//Attack1Montage = LoadObject<UAnimMontage>(nullptr, TEXT(" /arrow_z/Content/assets/animation/Attack1_Montage.uasset"));
	//Attack2Montage = LoadObject<UAnimMontage>(nullptr, TEXT("D:/Users/PARTH/Documents/Unreal Projects/c++/arrow_z/Content/assets/animation/Attack2_Montage.uasset"));
	//Attack3Montage = LoadObject<UAnimMontage>(nullptr, TEXT("D:/Users/PARTH/Documents/Unreal Projects/c++/arrow_z/Content/assets/animation/Attack3_Montage.uasset"));
	//--------------------------------------------------------------------------------------------------------------
	// Bind the OnMontageEnded event
	//OnMontageEnded.AddDynamic(this, &Aarrow_zCharacter::OnMontageEnded);
	UAnimInstance* anim_slot_1 = GetMesh()->GetAnimInstance();
	if (anim_slot_1 != nullptr)
	{
		anim_slot_1->OnMontageEnded.AddDynamic(this, &Aarrow_zCharacter::OnMontageEnded);
	}
	//--------------------------------------------------------------------------------------------------------------
	// Create and set the  static  mesh
	Weapon_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("secondary_Weapon_mesh"));

	//arrange order or attach 
	//Weapon_mesh->SetupAttachment(RootComponent);//set/order to rootmotion 
	Weapon_mesh->SetupAttachment(GetMesh(), TEXT("secondnary_weapon"));//set/order mesh to skeleton mesh(but doesnot change socket to inheritated componentWeapon_mesh->Sock(TEXT("secondnary_weapon"));//set socket location manually
	//Weapon_mesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(TEXT("secondnary_weapon")));//doent work as intened//attach/reorder to ue5 editor [but parent socket location can be set]//--------------------------------------------------------------------------------------------------------------

}

void Aarrow_zCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	//--------------------------------------------------------------------------------------------------------------
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	//UE_LOG(LogTemp, Warning, TEXT("Hello, this is a printed message in C++!"));
	//--------------------------------------------------------------------------------------------------------------

	
	//--------------------------------------------------------------------------------------------------------------
	/* 
	UAnimInstance* anim_slot_1 = GetMesh()->GetAnimInstance();
	if (anim_slot_1 != nullptr)
	{
		anim_slot_1->OnMontageEnded.AddDynamic(this, &Aarrow_zCharacter::OnMontageEnded);
	}*/
	//--------------------------------------------------------------------------------------------------------------

}

//////////////////////////////////////////////////////////////////////////
// Input

void Aarrow_zCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &Aarrow_zCharacter::Move);

		// sprinting
		EnhancedInputComponent->BindAction(Sprint_Action, ETriggerEvent::Started, this, &Aarrow_zCharacter::Sprint);
		EnhancedInputComponent->BindAction(Sprint_Action, ETriggerEvent::Completed, this, &Aarrow_zCharacter::Sprint_release);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &Aarrow_zCharacter::Look);

		// Dash
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &Aarrow_zCharacter::Dash);

		//interact
		EnhancedInputComponent->BindAction(Interact_Action, ETriggerEvent::Started, this, &Aarrow_zCharacter::Interact_action);

		//combat
		//EnhancedInputComponent->BindAction(Combat, ETriggerEvent::Started, this, &Aarrow_zCharacter::Combat);
		EnhancedInputComponent->BindAction(Combat_Action, ETriggerEvent::Started, this, &Aarrow_zCharacter::Combat);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void Aarrow_zCharacter::Move(const FInputActionValue& Value)
{
	//if (GEngine)
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("moveing"));

	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void Aarrow_zCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

/* 
void Aarrow_zCharacter::PrintMessage() {
	// log message
	UE_LOG(LogTemp, Warning, TEXT("Hello, this is a printed message in C++!"));
	//on screen message
	if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Hit actor:"));
			}
}*/
//--------------------------------------------------------------------------------------------------------------

//void Aarrow_zCharacter::demo(USkeletalMeshComponent* MeshComponent, UAnimInstance* demo_instance, UAnimMontage* MontageToPlay)
void Aarrow_zCharacter::demo()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("demo_play"));

	//demo_instance = GetMesh()->GetAnimInstance();
	//--------------------------------------------------------------------------------------------------------------
	PlayAnimMontage(demo_anim);//must be these
	//--------------------------------------------------------------------------------------------------------------
	

	// Bind OnMontageEnded event
	
	// Bind the function to the OnMontageEnded event
	GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &Aarrow_zCharacter::OndemoEnded);
	//notifybegin
	GetMesh()->GetAnimInstance()->OnPlayMontageNotifyBegin.AddDynamic(this, &Aarrow_zCharacter::note_begin);
	//notifyend
	GetMesh()->GetAnimInstance()->OnPlayMontageNotifyEnd.AddDynamic(this, &Aarrow_zCharacter::note_end);
	//unbinding
	//GetMesh()->GetAnimInstance()->OnMontageEnded.RemoveDynamic(this, &Aarrow_zCharacter::OndemoEnded);
	//--------------------------------------------------------------------------------------------------------------
	//OndemoEnded(demo_anim,false);//call function manually
}
 
void Aarrow_zCharacter::OndemoEnded(UAnimMontage* Montage, bool bInterrupted)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("demo_end"));

	//unbinding
	GetMesh()->GetAnimInstance()->OnMontageEnded.RemoveDynamic(this, &Aarrow_zCharacter::OndemoEnded);//if not unbinding face runtime error(remaining)

	
}
//void Aarrow_zCharacter::note_begin(UAnimMontage* Montage);
void Aarrow_zCharacter::note_begin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("notify_begin"));

}
void Aarrow_zCharacter::note_end(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("notify_end"));
}
//


//--------------------------------------------------------------------------------------------------------------
void Aarrow_zCharacter::Sprint(const FInputActionValue& Value)
{
	
	if (!bIsSprinting)
	{
		bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed *= SprintSpeedMultiplier;
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Started Sprinting"));
	}
}

void Aarrow_zCharacter::Sprint_release(const FInputActionValue& Value)
{
	if (bIsSprinting)
	{
		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed /= SprintSpeedMultiplier;
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Stopped Sprinting"));
	}
}
//--------------------------------------------------------------------------------------------------------------

void Aarrow_zCharacter::Dash(const FInputActionValue& Value)
{
	 
	// Get the character's forward vector
	FVector ForwardVector = GetActorForwardVector();

	// Calculate the dash direction (forward + 500 units)
	FVector DashDirection = ForwardVector * 2000.f;

	// Apply the dash impulse to the character
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	if (MovementComponent)
	{
		MovementComponent->AddImpulse(DashDirection, true);
		 GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("dash"));
	}
	
	//--------------------------------------------------------------------------------------------------------------

	//LaunchCharacter(FVector(2, 0, 1) * 1000, false, false);//only jump to fixed direction
	
	//--------------------------------------------------------------------------------------------------------------
	/* 
	//Directional dash based on player rotation
	FVector ForwardVector = GetActorForwardVector();
	FVector DashDirection = ForwardVector * 2000.f;

	LaunchCharacter(DashDirection, false, false);
	
	*/
	//--------------------------------------------------------------------------------------------------------------
	/* 
	// Calculate the dash force
	FVector ForwardVector = GetActorForwardVector() * 2000.0f;
	// Calculate the dash force
	float DashForce = 2000.0f; // Adjust as needed
	FVector DashForceVector = ForwardVector * DashForce;
	GetCharacterMovement()->AddForce(DashForceVector);
	*/
	
	//--------------------------------------------------------------------------------------------------------------
	/* 
	// Calculate the dash location
	FVector ForwardVector = GetActorForwardVector();
	float DashDistance = 2000.f;
	FVector DashLocation = GetActorLocation() + ForwardVector * DashDistance;
	
	// Move the character to the dash location
	SetActorLocation(DashLocation);
	*/
	
	//--------------------------------------------------------------------------------------------------------------

}
//--------------------------------------------------------------------------------------------------------------
void Aarrow_zCharacter::Interact_action(const FInputActionValue& Value)
{
	
	//line trace

	// Set up the parameters for the line trace
	FVector StartLocation = GetActorLocation(); // Starting point (usually your character's location)
	// Get the direction the camera is looking 
	FVector CameraForwardDir = FollowCamera->GetForwardVector();//camera forward direction
	//FVector EndLocation = StartLocation + (GetActorForwardVector() * 1500.0f); // Extend the line forward by 1500 units,as per mesh position
	FVector EndLocation = StartLocation + (CameraForwardDir * 1000.0f);//as per camera position
	
	FHitResult HitResult; // Stores the result of the trace

	// Perform the line trace
	FCollisionQueryParams TraceParams(FName(TEXT("LineTrace")), true, this);//?
	TraceParams.bTraceComplex = true; // Enable complex collision checks
	TraceParams.AddIgnoredActor(this); // Ignore the character itself

	// Perform the actual line trace
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECC_Visibility, // Collision channel (you can customize this)
		TraceParams
	);

 /* 
	//draw line 
	if (bHit)
	{
		// Handle the hit result (e.g., apply damage, interact with objects, etc.)
		// You can access HitResult.Actor, HitResult.Location, HitResult.Normal, etc.
		// For debugging, you can draw a line to visualize the trace:
		DrawDebugLine(GetWorld(), StartLocation, HitResult.Location, FColor::Red, false, 5.0f, 0, 1.0f);

		// Handle the hit result
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			FString ActorName = HitActor->GetName();
			FString DebugMessage = FString::Printf(TEXT("Hit actor: %s"), *ActorName);
			//UE_LOG(LogTemp, Warning, TEXT("Hit actor: %s"), *ActorName);

			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, DebugMessage);
			}
		
			// Destroy the actor
			//HitActor->Destroy();
		}
	}
	else
	{
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 5.0f, 0, 1.0f);
	}
	*/

	// Spawn a small cube at the hit location
	FVector SpawnLocation = EndLocation;
	FRotator SpawnRotation = FRotator::ZeroRotator; // You can customize the rotation
	FActorSpawnParameters SpawnParams;
	//Actor* SpawnedCube = GetWorld()->SpawnActor<AActor>(cp_interect::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
	//Aarrow_zCharacter* SpawnedCube = GetWorld()->SpawnActor<Aarrow_zCharacter>(SpawnLocation, SpawnRotation, SpawnParams);
	// SpawnedCube->SetActorScale3D(FVector(2.5f, 2.5f, 2.5f)); // You can customize the scale

	//Acp_interect* SpawnedCube = GetWorld()->SpawnActor<Acp_interect>(SpawnLocation, SpawnRotation, SpawnParams);
	ALightSwitchBoth* SpawnedCube = GetWorld()->SpawnActor<ALightSwitchBoth>(SpawnLocation, SpawnRotation, SpawnParams);
	if (SpawnedCube)
	{
		// Customize the cube's properties (e.g., material, scale, etc.)
		// ...
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("spawned"));
		}
	}
	
	
	//teleport at end location
	//SetActorLocation(EndLocation);
}
//--------------------------------------------------------------------------------------------------------------
void Aarrow_zCharacter::Combat(const FInputActionValue& Value)
{
	// Increment the number of clicks
	NumClicks++;

	// Reset the number of clicks after a delay
	FTimerHandle ClickTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(ClickTimerHandle, this, &Aarrow_zCharacter::ResetNumClicks, 0.5f, false);

	// Play the appropriate combo attack based on the number of clicks
	PlayComboAttack();
}

void Aarrow_zCharacter::ResetNumClicks()
{
	NumClicks = 0;
}

void Aarrow_zCharacter::PlayComboAttack()
{
	if (ComboAttackMontages.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No combo attack montages to play."));
		return;
	}

	MyAnimInstance = GetMesh()->GetAnimInstance();
	if (!MyAnimInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get animation instance."));
		return;
	}

	// Bind OnMontageEnded event
	MyAnimInstance->OnMontageEnded.RemoveDynamic(this, &Aarrow_zCharacter::OnMontageEnded);
	MyAnimInstance->OnMontageEnded.AddDynamic(this, &Aarrow_zCharacter::OnMontageEnded);

	// Determine the number of animations to play based on the number of clicks
	int32 NumAnimationsToPlay = FMath::Clamp(NumClicks, 0, ComboAttackMontages.Num());

	// Play the combo attack animations
	for (int32 Index = 0; Index < NumAnimationsToPlay; ++Index)
	{
		if (ComboAttackMontages.IsValidIndex(Index))
		{
			MyAnimInstance->Montage_Play(ComboAttackMontages[Index]);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Invalid montage index."));
		}
	}
}
 
void Aarrow_zCharacter::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	// Perform any necessary actions after the combo attack animations have ended
	// For example, resetting the combo state, allowing for new combos, etc.
}



//--------------------------------------------------------------------------------------------------------------
/*  combo 1
void Aarrow_zCharacter::StartComboAttack()
{
	if (!bIsAttacking)
	{
		bIsAttacking = true;
		HandleCombo();
	}
}

void Aarrow_zCharacter::HandleCombo()
{ FString ComboCountString = FString::FromInt(ComboCount);

	switch (ComboCount)
	{
	case 0:
		// Initial attack (play Attack1Montage)
		PlayAnimMontage(Attack1Montage);
		//ComboCount = 1;
		ComboCount++;

		// Convert the integer value to FString
		

		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("1st"));
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, ComboCount);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, ComboCountString);
		break;
	case 1:
		// Second attack (play Attack2Montage)
		PlayAnimMontage(Attack2Montage);
		//ComboCount = 2;
		ComboCount++;

		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("2nd"));
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, ComboCountString);
		break;
	case 2:
		// Third attack (play Attack3Montage)
		PlayAnimMontage(Attack3Montage);
		ComboCount = 0; // Reset combo

		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("3rd"));
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, ComboCountString);
		break;
	default:
		// Invalid state (shouldn't happen)
		break;
	}
	// Increment ComboCount after playing the animation montage
	ComboCount = (ComboCount + 1) % 3; // Ensure ComboCount loops back to 0 after reaching 2
}
void Aarrow_zCharacter::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (bIsAttacking)
	{
		//bIsAttacking = false;
		// Handle any post-attack logic here (e.g., allow next attack)
	}
	HandleCombo();
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("MONTAGE END"));
}
*/
//--------------------------------------------------------------------------------------------------------------

// combo_2
void Aarrow_zCharacter::HandleOnMontageNotifyBegin(FName a_nNotifyName, const FBranchingPointNotifyPayload& a_pBranchingPayload)
{// Decrement Combo Index
	m_iComboAttackIndex--;
	// Stop Montage if below zero
	if (m_iComboAttackIndex < 0)
	{
		// Get Anim Instance
		UAnimInstance* pAnimInst = GetMesh()->GetAnimInstance();
		if (pAnimInst != nullptr)
		{
			pAnimInst->Montage_Stop(0.4f, m_pLight_AttackMontage);
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("play begin"));

		}
	}
}
void Aarrow_zCharacter::LightAttack()
{
	//combo2 
	// Bind Anim Events
	UAnimInstance* pAnimInst = GetMesh()->GetAnimInstance();
	if (pAnimInst != nullptr)
	{
		pAnimInst->OnPlayMontageNotifyBegin.AddDynamic(this, &Aarrow_zCharacter::HandleOnMontageNotifyBegin);
	}
	//

	// Need to not already be attacking and must be on the ground
    //if (!IsAttacking() && CanJump())
	if (!IsAttacking())
	{
		// Get the animation instance
		//UAnimInstance* pAnimInst = GetMesh()->GetAnimInstance();
		if (pAnimInst != nullptr)
		{
			// Play Light Attack
			if (m_pLight_AttackMontage != nullptr)
			{
				pAnimInst->Montage_Play(m_pLight_AttackMontage);

				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("light attack"));
			}
		}
	}
	else
	{
		m_iComboAttackIndex = 1;
	}


}
bool Aarrow_zCharacter::IsAttacking()
{
	// Return true if any attack montage is playing
	UAnimInstance* pAnimInst = GetMesh()->GetAnimInstance();
	if (pAnimInst != nullptr)
	{
		if (pAnimInst->Montage_IsPlaying(m_pLight_AttackMontage))
		{
			return true;
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("is attacking"));
		
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("not attacking"));
	return false;
}//


