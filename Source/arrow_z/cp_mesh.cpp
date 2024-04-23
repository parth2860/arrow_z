// Fill out your copyright notice in the Description page of Project Settings.


#include "cp_mesh.h"
#include "Components/BoxComponent.h"// Include the BoxComponent header file
//#include "Components/StaticMeshComponent.h" // Include the StaticMeshComponent header file
#include "arrow_zCharacter.h" // Include the character header file

// Sets default values
Acp_mesh::Acp_mesh()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    //-----------------------------------------------------------------------------------------
    /* 
    // Create a static mesh component
    CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube Mesh"));

    // Load the Cube mesh (you can replace this with your own cube mesh asset)
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
    if (CubeMeshAsset.Succeeded())
    {
        CubeMesh->SetStaticMesh(CubeMeshAsset.Object);
    }

    // Set the cube mesh as the root component
    RootComponent = CubeMesh;
    */
    //-----------------------------------------------------------------------------------------
    // Create and set the sphere static  mesh
    SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh_1"));
    RootComponent = SphereMesh;

    // Load a static mesh (e.g., a sphere)
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("StaticMesh'/Game/Path/To/Your/SphereMesh.SphereMesh'"));
    if (SphereMeshAsset.Succeeded())
    {
        SphereMesh->SetStaticMesh(SphereMeshAsset.Object);
    }
    //-----------------------------------------------------------------------------------------
    // Create the Box Collision Component
    BoxCollisionarea = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionarea"));
    BoxCollisionarea->SetBoxExtent(FVector(100.f, 100.f, 100.f)); // Set the box dimensions
    BoxCollisionarea->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); // Set collision type (query and physics)
    BoxCollisionarea->SetCollisionObjectType(ECollisionChannel::ECC_Pawn); // Set your desired collision channel
    BoxCollisionarea->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

    // Bind the overlap function to the OnComponentBeginOverlap event
    BoxCollisionarea->OnComponentBeginOverlap.AddDynamic(this, &Acp_mesh::OnBoxOverlap);
    BoxCollisionarea->OnComponentEndOverlap.AddDynamic(this, &Acp_mesh::OnBoxOverlapEnd);
    //MyBoxCollisionarea->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    //-----------------------------------------------------------------------------------------
}

// Called when the game starts or when spawned
void Acp_mesh::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Acp_mesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    //FRotator NewRotation = GetActorRotation() + FRotator(0.0f, DeltaTime * 50.0f, 0.0f); // Adjust the rotation speed as needed
    //SetActorRotation(NewRotation);

}
void Acp_mesh::SetRotationSpeed(float Speed, float DeltaTime)
{
    // Set default rotation speed
    // float RotationSpeed = 100.0f;
    RotationSpeed = 100.0f;
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

void Acp_mesh::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    //cast to charcter
    Aarrow_zCharacter* Player = Cast<Aarrow_zCharacter>(OtherActor);
    if (Player)
    {
        // Attach the weapon mesh to the player (e.g., to the hand socket)
        //SphereMesh->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "secondnary_weapon");
        // Assuming SphereMesh is your weapon mesh component
        //GetRootComponent()->AttachToActor(Player->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "secondnary_weapon");
        //----------------------------------
        // Attach the weapon to the First Person Character
        FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
        //SphereMesh->AttachToComponent(Player->GetMesh(), AttachmentRules, FName(TEXT("secondnary_weapon")));//get attach to player
        SphereMesh->AttachToComponent(Player->Weapon_mesh, AttachmentRules, FName(TEXT("secondnary_weapon")));//get attach to player specific mesh
        //----------------------------------

    }
    
    
}
void Acp_mesh::OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

