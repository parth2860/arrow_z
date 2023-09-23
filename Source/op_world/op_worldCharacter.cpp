// Copyright Epic Games, Inc. All Rights Reserved.

#include "op_worldCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/Engine.h" // Include this for UE_LOG
#include "DrawDebugHelpers.h" // Include this for debug drawing
#include "NavigationSystem.h" // Include NavigationSystem for navigation functionality
#include "Kismet/GameplayStatics.h" // Include the header for UGameplayStatics
#include "CableComponent.h"
//#include "AI/Navigation/NavigationSystem.h"
#include "GameFramework/PlayerController.h"
//#include "GrapplingHook.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"
#include "Engine/TimelineTemplate.h"

//////////////////////////////////////////////////////////////////////////
// Aop_worldCharacter

Aop_worldCharacter::Aop_worldCharacter()
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

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++) 
	
	// Set default values for line trace
	TraceDistance = 5000.0f;
	float SwingSpeed = 5000.0f;

	// Declare the timeline component
	UTimelineComponent* MovementTimeline;

	// Declare the curve float
	UCurveFloat* CurveFloat;

	// Declare the timeline float interp function
	FOnTimelineFloat InterpFunction;

	// Initialize the timeline component
	MovementTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("MovementTimeline"));

	// Initialize the curve float (you can load a curve asset here)
	CurveFloat = nullptr; // Set this to the actual curve you want to use

	// Bind the interp function to your desired function
	InterpFunction.BindUFunction(this, FName(TEXT("YourInterpFunction")));

	// Add the float curve to the timeline
	MovementTimeline->AddInterpFloat(CurveFloat, InterpFunction);

	// Create the cable component
	CableComponent = CreateDefaultSubobject<UCableComponent>(TEXT("CableComponent"));

	// Attach the cable component to the root component (e.g., CapsuleComponent)
	//CableComponent->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	// Attach the cable component to the character's mesh component (change to your specific mesh component)
	//CableComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);


}

void Aop_worldCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
			UE_LOG(LogTemp, Warning, TEXT("begin play"));
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void Aop_worldCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &Aop_worldCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &Aop_worldCharacter::Look);

		//fire with enhanced input)
		//EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &Aop_worldCharacter::Fire);

		// Bind the function to move the player forward to the "MoveForward" input action
		PlayerInputComponent->BindAxis("MoveForward", this, &Aop_worldCharacter::MoveForward);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &Aop_worldCharacter::Move);
	}
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind left mouse button click event(without enhanced input)
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &Aop_worldCharacter::Fire);
	
	// Bind the function to move the player forward to the "MoveForward" input action
	//PlayerInputComponent->BindAxis("MoveForward", this, &Aop_worldCharacter::MoveForward);

}
// Function to move the player forward
void Aop_worldCharacter::MoveForward(float Value)
{
	// Calculate the forward vector
	//FVector ForwardVector = GetActorForwardVector();

	// Move the player forward based on the input value
	//AddMovementInput(ForwardVector, Value);
}
void Aop_worldCharacter::Move(const FInputActionValue& Value)
{
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

void Aop_worldCharacter::Look(const FInputActionValue& Value)
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

void Aop_worldCharacter::Fire()
{

		
		//UE_LOG(LogTemp, Warning, TEXT("fire."));

		PerformLineTrace();
		Swing();
		//AGrapplingHook();
		//StartGrapplingHook();
		//StopGrapplingHook();
	//	HandleGrapplingHook();
}
/*

void Aop_worldCharacter::PerformLineTrace()
{
	// Get the player's viewpoint
	FVector StartLocation;
	FRotator ViewRotation;
	GetActorEyesViewPoint(StartLocation, ViewRotation);

	// Calculate the end location for the line trace
	TraceStart = StartLocation;
	TraceEnd = StartLocation + (ViewRotation.Vector() * TraceDistance);

	// Perform the line trace
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this); // Ignore the player character

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult,TraceStart,TraceEnd,ECC_Visibility,CollisionParams);

	// Check if we hit something
		if (bHit)
		{
			// Handle what happens when we hit something (e.g., apply damage to the hit actor)
			AActor* HitActor = HitResult.GetActor();
			 if (HitActor)
			{

				 //-------------------------
				  // Get the player controller
				 APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
				 if (PlayerController)
				 {
					 // Set the player's location to the hit location
					// PlayerController->GetPawn()->SetActorLocation(HitResult.Location);

					 //-----
						
					 //---------
				 }
				 
				 //-------------------------------
					// Check if the player character exists and has a character movement component
							 //ACharacter* PlayerCharacter = Cast<ACharacter>(GetOwner());
							 //if (PlayerCharacter && PlayerCharacter->GetCharacterMovement())
							 //{
								// // Get the hit location
								// FVector HitLocation = HitResult.Location;

								// // Calculate the direction from the player's current location to the hit location
								// FVector Direction = HitLocation - PlayerCharacter->GetActorLocation();
								// Direction.Normalize();
								// float SwingSpeed = 5000.0f;

								// // Apply a force to the character's capsule component to move it towards the hit location
								// //PlayerCharacter->GetCapsuleComponent()->AddImpulse(Direction * SwingSpeed);

								// // set the character's velocity to move towards the hit location
								////PlayerCharacter->GetCapsuleComponent()->Velocity=Direction * SwingSpeed;

								// // Set the character's velocity to move towards the hit location
								////PlayerCharacter->GetCharacterMovement()->Velocity = Direction * SwingSpeed;

								// // Apply an impulse to make the character jump towards the hit location
								// float JumpImpulse = 1000.0f; // Adjust this value as needed
								// //PlayerCharacter->LaunchCharacter(Direction * JumpImpulse, false, false);

								// // Optionally, you can play a swinging animation here
							 //}
				 //---------------------------------
				 // ------------------------------
			}
		}

	// For debugging purposes, draw a line in the editor to visualize the line trace
	if (GetWorld() && bHit)
	{
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 5, 0, 1);
	}
}*/
/*
void  Aop_worldCharacter::AGrapplingHook()
{
	// Set up the grappling hook's mesh, collision, and other components.
	GrapplingHook = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GrapplingHookMesh"));
	GrapplingHook->SetupAttachment(RootComponent);  // Attach it to the root component or any appropriate component.

	static ConstructorHelpers::FObjectFinder<UStaticMesh> GrapplingHookMeshAsset(TEXT("/Game/Path/To/GrapplingHookMesh.GrapplingHookMesh"));
	if (GrapplingHookMeshAsset.Succeeded())
	{
		GrapplingHook->SetStaticMesh(GrapplingHookMeshAsset.Object);
	}
	GrapplingHook->SetRelativeLocation(FVector(0, 0, 0)); // Adjust the location as needed.
	GrapplingHook->SetRelativeRotation(FRotator(0, 0, 0)); // Adjust the rotation as needed.

}
void  Aop_worldCharacter::StartGrapplingHook()
{
	if (!GrapplingHook)
	{
		// Spawn and attach the grappling hook to the character.
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		GrapplingHook = GetWorld()->SpawnActor<AGrapplingHook>(GrapplingHookClass, GetActorLocation(), FRotator::ZeroRotator, SpawnParams);

		if (GrapplingHook)
		{
			// Implement the logic for firing the grappling hook.
			GrapplingHook->FireGrapple(GetActorLocation(), GetControlRotation().Vector());
		}
	}
}

void  Aop_worldCharacter::StopGrapplingHook()
{
	if (GrapplingHook)
	{
		// Implement the logic to stop and detach the grappling hook.
		GrapplingHook->StopGrapple();
		GrapplingHook->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		GrapplingHook->Destroy();
		GrapplingHook = nullptr;
	}
}

void  Aop_worldCharacter::HandleGrapplingHook()
{
	if (GrapplingHook)
	{
		// Implement the logic for moving towards the grappling hook target.
		// Calculate the direction from the character to the hook's location.
		FVector HookLocation = GrapplingHook->GetActorLocation();
		FVector CharacterLocation = GetActorLocation();
		FVector Direction = (HookLocation - CharacterLocation).GetSafeNormal();

		// Apply forces or adjustments to the character's position to move it towards the hook.
		FVector NewLocation = CharacterLocation + Direction * GrappleSpeed * GetWorld()->DeltaTimeSeconds;
		SetActorLocation(NewLocation);

		// Optionally, you can play animations or effects here.
	}
}


void Aop_worldCharacter::Fire(const FInputActionValue& Value)
{
	//FVector2D LookAxisVector = Value.Get<FVector2D>();
	//if (Controller != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("fire2."));
	}
}*/

// Declare a class variable to store the hit location
FVector HitLocation;
void Aop_worldCharacter::PerformLineTrace()
{
	// Get the player's viewpoint
	FVector StartLocation;
	FRotator ViewRotation;
	GetActorEyesViewPoint(StartLocation, ViewRotation);

	// Calculate the end location for the line trace
	TraceStart = StartLocation;
	TraceEnd = StartLocation + (ViewRotation.Vector() * TraceDistance);

	// Perform the line trace
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this); // Ignore the player character

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionParams);

	// Check if we hit something
	if (bHit)
	{	//---------------------------------------------------------------------------------
		 // Handle what happens when we hit something (e.g., apply damage to the hit actor)
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			// Check if the hit actor is a cube
			//ACubeActor* CubeActor = Cast<ACubeActor>(HitActor);
			  Acp_wepon* Acp_wepon = Cast<Acp_wepon>(HitActor);
			if (Acp_wepon)
			{
				// Swap the locations of the player and the cube
				FVector PlayerLocation = GetActorLocation();
				FVector CubeLocation = Acp_wepon->GetActorLocation();

				SetActorLocation(CubeLocation);
				Acp_wepon->SetActorLocation(PlayerLocation);

				// Call any additional logic for the swap
				//HandleSwap(PlayerLocation, CubeLocation);
			}
		}
		//---------------------------------------------------------------------------------

		// Handle what happens when we hit something (e.g., apply damage to the hit actor)
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			// Store the hit location in the class variable
			HitLocation = HitResult.Location;

			// Get the player controller
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (PlayerController)
			{
				// Set the player's location to the hit location
				PlayerController->GetPawn()->SetActorLocation(HitResult.Location);

				// Call the Swing function
				Swing();
			}
		}
	}

	// For debugging purposes, draw a line in the editor to visualize the line trace
	if (GetWorld() && bHit)
	{
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 5, 0, 1);
	}
}

void Aop_worldCharacter::Swing()
{
	// Check if the player character exists and has a character movement component
	ACharacter* PlayerCharacter = Cast<ACharacter>(GetOwner());
	if (PlayerCharacter && PlayerCharacter->GetCharacterMovement())
	{
		// Calculate the direction from the player's current location to the stored hit location
		FVector Direction = HitLocation - PlayerCharacter->GetActorLocation();
		Direction.Normalize();

		// Calculate the cross product with the up vector to determine the right vector for swinging
		FVector RightVector = FVector::CrossProduct(Direction, FVector::UpVector);
		RightVector.Normalize();

		// Apply a force to simulate the swinging motion
		float SwingForce = 5000.0f; // Adjust this value as needed
		FVector SwingImpulse = RightVector * SwingForce;

		// Apply the impulse to the character's capsule component
		UPrimitiveComponent* CharacterCapsuleComponent = PlayerCharacter->FindComponentByClass<UCapsuleComponent>();
		if (CharacterCapsuleComponent)
		{
			CharacterCapsuleComponent->AddImpulse(SwingImpulse);
		}

		// Set the character's movement mode to flying
		PlayerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);

		// Set up the cable component
		if (CableComponent)
		{
			// Attach one end of the cable to the player's root component (e.g., the capsule component)
			CableComponent->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);

			// Set the other end of the cable to the hit location
			CableComponent->SetRelativeLocation(HitLocation);
			CableComponent->SetVisibility(true);
		}

		// Set up the cable component
		//if (CableComponent)
		{
			// Attach one end of the cable to the player's root component
			//CableComponent->AttachToComponent(PlayerCharacter->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
			// Attach the cable component to the character's mesh component (change to your specific mesh component)
			//CableComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
			// Attach the cable component to the root component (e.g., CapsuleComponent)
			//CableComponent->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);

			// Set the other end of the cable to the hit location
			//CableComponent->SetRelativeLocation(HitLocation);
			//CableComponent->SetVisibility(true);
		}
	}
}







