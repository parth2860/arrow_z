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

	}
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind left mouse button click event(without enhanced input)
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &Aop_worldCharacter::Fire);
	


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

		
		UE_LOG(LogTemp, Warning, TEXT("fire."));

		PerformLineTrace();
	
}
/* 
void Aop_worldCharacter::Fire(const FInputActionValue& Value)
{
	//FVector2D LookAxisVector = Value.Get<FVector2D>();
	//if (Controller != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("fire2."));
	}
}*/

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

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		TraceStart,
		TraceEnd,
		ECC_Visibility,
		CollisionParams
	);

	// Check if we hit something
	if (bHit)
	{
		// Handle what happens when we hit something (e.g., apply damage to the hit actor)
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			// Handle the hit actor here
			// For example, apply damage, show a hit effect, etc.
		}
	}

	// For debugging purposes, draw a line in the editor to visualize the line trace
	if (GetWorld() && bHit)
	{
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1, 0, 1);
	}
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

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		TraceStart,
		TraceEnd,
		ECC_Visibility,
		CollisionParams
	);

	// Check if we hit something
if (bHit)
{
    // Handle what happens when we hit something (e.g., apply damage to the hit actor)
    AActor* HitActor = HitResult.GetActor();
    if (HitActor)
    {
        // Get the controller
        AController* MyController = GetController();
        if (MyController)
        {
            UNavigationSystemBase* NavSystemBase = GetWorld()->GetNavigationSystem();
            if (NavSystemBase)
            {
                // Cast to the correct navigation system type
                UNavigationSystemV1* NavSystem = Cast<UNavigationSystemV1>(NavSystemBase);
                if (NavSystem)
                {
                    // Check if the hit location is reachable
                    FNavLocation TargetLocation;
                    if (NavSystem->GetRandomPointInNavigableRadius(HitResult.Location, TraceDistance, TargetLocation))
                    {
                       // MyController->MoveToLocation(TargetLocation.Location);
                    }
                }
            }
        }
    }
}



	// For debugging purposes, draw a line in the editor to visualize the line trace
	if (GetWorld() && bHit)
	{
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1, 0, 1);
	}
}*/



