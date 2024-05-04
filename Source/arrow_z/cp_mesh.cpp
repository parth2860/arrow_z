// Fill out your copyright notice in the Description page of Project Settings.


#include "cp_mesh.h"
#include "Components/BoxComponent.h"// Include the BoxComponent header file
//#include "Components/StaticMeshComponent.h" // Include the StaticMeshComponent header file
#include "arrow_zCharacter.h" // Include the character header file
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshSocket.h"

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
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));//it worked,,by deafault path for engine assets
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

    //----------------------------------------------------------------------------------------------
    // loading option
    //static ConstructorHelpers::FObjectFinder<UStaticMesh> sbMesh(TEXT("Material'/Game/Materials/skyboxes/mat_skybox_backdrop02.mat_skybox_backdrop02'"));
    //static ConstructorHelpers::FObjectFinder<UMaterial> sbMaterial(TEXT("Material'/Game/Materials/skyboxes/mat_skybox_backdrop02.mat_skybox_backdrop02'"));
    //----------------------------------------------------------------------------------------------
    // Load a static mesh (e.g., a sphere)//arrow_z/Content/assets/3d_mesh/Sword.uasset
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("StaticMesh'/Game/assets/3d_mesh/Sword.Sword'"));//remove content folder for custom access
    if (SphereMeshAsset.Succeeded())
    {
        SphereMesh->SetStaticMesh(SphereMeshAsset.Object);
    }
    //-----------------------------------------------------------------------------------------
    // Create the Box Collision Component
    BoxCollisionarea = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionarea"));
    BoxCollisionarea->SetBoxExtent(FVector(20.f, 20.f, 100.f)); // Set the box dimensions
    //BoxCollisionarea->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); // Set collision type (query and physics)
    //BoxCollisionarea->SetCollisionObjectType(ECollisionChannel::ECC_Pawn); // Set your desired collision channel
    BoxCollisionarea->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    //additional collision query
    //SphereMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    //SphereMesh->SetCollisionResponseToAllChannels(ECollisionResponse::Ignore);
    //SphereMesh->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::Overlap);
    // 
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
        //SphereMesh->AttachToComponent(Player->GetMesh(), AttachmentRules, FName(TEXT("secondnary_weapon")));//get attach to player//collision also attached
        SphereMesh->AttachToComponent(Player->Weapon_mesh, AttachmentRules, FName(TEXT("secondnary_weapon")));//get attach to player specific mesh
        //SphereMesh->AttachToActor(Player->Weapon_mesh, AttachmentRules, FName(TEXT("secondnary_weapon")));
        // Ensure collision is disabled after attachment to prevent obstruction
        SphereMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);//remove collision
        //----------------------------------
        //GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("equiped"));//event after attach its keeps printing

        // Unregister from the Overlap Event so it is no longer triggered
        //.RemoveAll(this);
        second_trace(OtherActor);
    }
    
    
}
void Acp_mesh::OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
void Acp_mesh::second_trace(AActor* OtherActor)
{
   
    /* 
    Aarrow_zCharacter* Player = Cast<Aarrow_zCharacter>(OtherActor);
    //Aarrow_zCharacter* Player = Cast<Aarrow_zCharacter>(GetOwner());
    // Get the class of the object
    //UClass* PlayerClass = Player->GetClass();

    if (Player)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player is valid."));
        if (Player->Weapon_mesh)
        {
            UE_LOG(LogTemp, Warning, TEXT("Weapon mesh is valid."));
            FName SocketName = Player->Weapon_mesh->GetAttachSocketName();
            FString SocketNameString = SocketName.ToString();
            UE_LOG(LogTemp, Warning, TEXT("Weapon Mesh Attach Socket Name: %s"), *SocketNameString);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Weapon mesh is invalid."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Player is invalid."));
    }
   */
    /*
       // Assuming you have a valid SphereMesh pointer
        if (SphereMesh)
        {
            // Get the static mesh associated with the static mesh component
            UStaticMesh* StaticMesh = SphereMesh->GetStaticMesh();

            // Ensure the static mesh is valid
            if (StaticMesh)
            {
                // Get the number of sockets in the static mesh
                int32 NumSockets = StaticMesh->Sockets.Num();

                // Array to hold socket names
                TArray<FName> SocketNames;

                // Iterate through sockets and add their names to the array
                for (int32 i = 0; i < NumSockets; ++i)
                {
                    SocketNames.Add(StaticMesh->Sockets[i]->SocketName);
                }

                // Now you have an array of socket names attached to the static mesh
                for (const auto& SocketName : SocketNames)
                {
                    // Do something with each socket name, such as printing it
                    UE_LOG(LogTemp, Warning, TEXT("Socket Name: %s"), *SocketName.ToString());
                }
            }
        }

    */  
        // 
        if (SphereMesh)
        {
            // Get the static mesh associated with the static mesh component
            UStaticMesh* StaticMesh = SphereMesh->GetStaticMesh();

            // Ensure the static mesh is valid
            if (StaticMesh)
            {
                // Get the number of sockets in the static mesh
                int32 NumSockets = StaticMesh->Sockets.Num();

                // Perform line trace from each socket location
                for (int32 i = 0; i < NumSockets; ++i)
                {
                    const FVector StartLocation = StaticMesh->Sockets[0]->RelativeLocation;
                    const FVector EndLocation = StaticMesh->Sockets[1]->RelativeLocation;

                    FHitResult HitResult;
                    //FCollisionQueryParams Params(FName(TEXT("SocketTrace")), false, SphereMesh->GetOwner());
                    FCollisionQueryParams Params;
                    Params.AddIgnoredActor(SphereMesh->GetOwner()); // Ignore the owner actor in the line trace
                    Params.bTraceComplex = false;
                    //Params.bTraceAsyncScene = true;
                    Params.bReturnPhysicalMaterial = true;

                    // Perform the line trace
                    if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params))
                    {
                        // If hit, print hit location
                        UE_LOG(LogTemp, Warning, TEXT("Socket Name: %s, Hit Location: %s"), *StaticMesh->Sockets[i]->SocketName.ToString(), *HitResult.Location.ToString());
                        DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 5.0f, ECC_WorldStatic, 1.0f);

                    }
                    else
                    {
                        // If no hit, print end location
                        UE_LOG(LogTemp, Warning, TEXT("Socket Name: %s, No Hit, End Location: %s"), *StaticMesh->Sockets[i]->SocketName.ToString(), *EndLocation.ToString());
                    }
                }
            }
        }






        //
}
