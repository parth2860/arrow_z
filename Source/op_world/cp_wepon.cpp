// Fill out your copyright notice in the Description page of Project Settings.


#include "cp_wepon.h"

// Sets default values
Acp_wepon::Acp_wepon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Create a CubeMeshComponent and set it as the RootComponent
    CubeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMeshComponent"));
    RootComponent = CubeMeshComponent;

    // Set the mesh for the cube
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
    if (CubeMeshAsset.Succeeded())
    {
        CubeMeshComponent->SetStaticMesh(CubeMeshAsset.Object);
    }
}

// Called when the game starts or when spawned
void Acp_wepon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Acp_wepon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // Rotate the cube
    FRotator NewRotation = GetActorRotation() + FRotator(0.0f, DeltaTime * 50.0f, 0.0f); // Adjust the rotation speed as needed
    SetActorRotation(NewRotation);

    
   // UE_LOG(LogTemp, Warning, TEXT("cube."));

}
void Acp_wepon::MoveSphereToPlayerLocation()
{
    // Get a reference to the player character
    ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0); // Assumes player 0, adjust as needed

    if (PlayerCharacter)
    {
        // Get the player's location
        FVector PlayerLocation = PlayerCharacter->GetActorLocation();

        // Set the sphere's location to the player's location
        SetActorLocation(PlayerLocation);
    }
}
void Acp_wepon::show()
{
	UE_LOG(LogTemp, Warning, TEXT("show_data."));
}

