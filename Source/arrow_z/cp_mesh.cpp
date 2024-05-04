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
    //get actor,attched actor,socket anme + line trace
	if (USkeletalMeshComponent* SkeletalMeshComponent = GetOwner())
	{
		// Get all attached children components
		const TArray<USceneComponent*>& AttachedComponents = SkeletalMeshComponent->GetAttachChildren();

		// Iterate through the attached components
		for (USceneComponent* AttachedComponent : AttachedComponents)
		{
			// Check if the attached component is a static mesh component
			if (UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(AttachedComponent))
			{
				// Print the name of the attached static mesh component (socket)
				//UE_LOG(LogTemp, Warning, TEXT("Attached Component Name: %s"), *StaticMeshComponent->GetName());

				// If the attached component is named "sword_mesh", get its socket names and locations
				if (StaticMeshComponent->GetName() == "sword_mesh")
				{
					//print socket name
					// Get the names of all sockets associated with the static mesh component
					TArray<FComponentSocketDescription> SocketDescriptions;
					StaticMeshComponent->QuerySupportedSockets(SocketDescriptions);

					// Print the names of all sockets
					for (const FComponentSocketDescription& SocketDescription : SocketDescriptions)
					{
						UE_LOG(LogTemp, Warning, TEXT("Socket Name: %s"), *SocketDescription.Name.ToString());
					}
					//
                    //  
					//print socket location
					// Get the locations of the "start_trace" and "end_trace" sockets
					FVector StartTraceLocation = StaticMeshComponent->GetSocketLocation(TEXT("start_trace"));
					FVector EndTraceLocation = StaticMeshComponent->GetSocketLocation(TEXT("end_trace"));

					//print socket location
					//UE_LOG(LogTemp, Warning, TEXT("Start Trace Location: %s"), *StartTraceLocation.ToString());
					//UE_LOG(LogTemp, Warning, TEXT("Start Trace Location: %s"), *EndTraceLocation.ToString());

					// Perform line trace from start to end trace
					FHitResult HitResult;
					FCollisionQueryParams Params;
					//Params.AddIgnoredActor(GetOwner()); // Ignore the owner actor in the line trace
					Params.AddIgnoredActor(SkeletalMeshComponent->GetOwner()); // Ignore the owner actor in the line trace
					Params.bTraceComplex = false;
					//Params.bTraceAsyncScene = true;
					Params.bReturnPhysicalMaterial = true;


					// Perform the line trace
					bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartTraceLocation, EndTraceLocation, ECollisionChannel::ECC_Visibility, Params);

					// Check if we hit something
					if (bHit)
					{
						// Handle the hit result (you can print debug information or perform other actions here)
						UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *HitResult.GetActor()->GetName());
						DrawDebugLine(GetWorld(), StartTraceLocation, EndTraceLocation, FColor::Red, false, 5.0f, ECC_WorldStatic, 1.0f);
						//DrawDebugLine(GetWorld(), StartTraceLocation, EndTraceLocation, FColor::Red, false, 5.0f, 0, 1.0f);

					}
					else
					{
						// No hit, print debug information
						UE_LOG(LogTemp, Warning, TEXT("Line trace did not hit anything."));
						DrawDebugLine(GetWorld(), StartTraceLocation, EndTraceLocation, FColor::Green, false, 5.0f, ECC_WorldStatic, 1.0f);
					}
					//
				}
			}
		}
	}
    
    */

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
    //
    Aarrow_zCharacter* Player = Cast<Aarrow_zCharacter>(OtherActor);
    //UClass* PlayerClass = Player->GetClass();

   

   
    //  
}
