// Fill out your copyright notice in the Description page of Project Settings.


#include "cp_exp.h"

// Sets default values
Acp_exp::Acp_exp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//--------------------------------------------------
	//DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	//RootComponent = DefaultSceneRoot;

	//Cylinder = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cl1"));
	//Cylinder->SetupAttachment(RootComponent);
 //   Cylinder->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	////set static mesh
	//Cylinder->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'")).Object);
 // 
	//// Create a rotation you want to set
	//FRotator NewRotation = FRotator(0.0f, 90.0f, 0.0f); // This sets a rotation of 90 degrees around the Y-axis

	// Set the component's world rotation
	//Cylinder->SetWorldRotation(NewRotation);
	//Cylinder->SetActorRotation(NewRotation);
	
	//RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
	//--------------------------------------------------
	// Create and set the sphere mesh
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh_1"));
	RootComponent = SphereMesh;

	// Load a static mesh (e.g., a sphere)
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("StaticMesh'/Game/Path/To/Your/SphereMesh.SphereMesh'"));
	if (SphereMeshAsset.Succeeded())
	{
		SphereMesh->SetStaticMesh(SphereMeshAsset.Object);
	}

	// Set default rotation speed
	RotationSpeed = 100.0f;
	//--------------------------------------------------
}

// Called when the game starts or when spawned
void Acp_exp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Acp_exp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//FRotator NewRotation = GetActorRotation() + FRotator(0.0f, DeltaTime * 50.0f, 0.0f); // Adjust the rotation speed as needed
	//SetActorRotation(NewRotation);
}
// Function to set the rotation speed of the sphere
void Acp_exp::SetRotationSpeed(float Speed, float DeltaTime)
{
	RotationSpeed = Speed;

	// Rotate the sphere
	//FRotator NewRotation = GetActorRotation() + FRotator(0.0f, DeltaTime * 50.0f, 0.0f); // Adjust the rotation speed as needed
	//SetActorRotation(NewRotation);

	// Get the player's input for forward movement
	float ForwardInput = GetInputAxisValue("MoveForward"); // Assuming "MoveForward" is the input axis name

	// Calculate the new rotation based on player input and delta time
	FRotator NewRotation = GetActorRotation() + FRotator(0.0f, ForwardInput * RotationSpeed * DeltaTime, 0.0f);

	// Set the actor's rotation
	SetActorRotation(NewRotation);
}

