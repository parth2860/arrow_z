// Fill out your copyright notice in the Description page of Project Settings.


#include "cp_interect.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
//#include "Engine/Engine.h"

// Sets default values
Acp_interect::Acp_interect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//box_area = CreateDefaultSubobject<UBoxComponent>(TEXT("box_area"));
	//BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	//RootComponent = BoxCollision;

	// Create the Box Collision Component
	MyBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBoxCollision"));
	MyBoxCollision->SetBoxExtent(FVector(50.f, 50.f, 50.f)); // Set the box dimensions
	MyBoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); // Set collision type (query and physics)
	MyBoxCollision->SetCollisionObjectType(ECollisionChannel::ECC_Pawn); // Set your desired collision channel
	RootComponent = MyBoxCollision; // Set the root component

	// Bind the overlap function to the OnComponentBeginOverlap event
	MyBoxCollision->OnComponentBeginOverlap.AddDynamic(this, &Acp_interect::OnBoxOverlap);
	//MyBoxCollision->OnComponentEndOverlap.AddDynamic(this, &Acp_interect::OnBoxOverlapEnd);
	//MyBoxCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	// 
	//plane
	mesh_plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//mesh_plane->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
    //mesh_plane->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	//mesh_plane->SetRelativeTransform(FTransform(FRotator(0.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f)));
	//mesh_plane->AddRelativeRotation(FRotator(5.0f, 5.0f, 5.0f));
    mesh_plane->SetWorldRotation(FRotator(5.0f, 5.0f, 5.0f));
	mesh_plane->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

    //arrow
	arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));

}

// Called when the game starts or when spawned
void Acp_interect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Acp_interect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void Acp_interect::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Handle the overlap event here
	if (OtherActor)
	{
		// log message for debugging
		UE_LOG(LogTemp, Warning, TEXT("Box overlapped with actor: %s"), *OtherActor->GetName());
		//print message in screen
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("overlapped inside"));
	}
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("inside"));

	//UWorld::SpawnActor();
	//UClass* ActorClassToSpawn = LightSwitchBoth::StaticClass();
	//FTransform SpawnTransform = FTransform::Identity; // Set your desired transform
	//AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorClassToSpawn, SpawnTransform);
}
//void Acp_interect::OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
void Acp_interect::OnBoxOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Handle the overlap event here
	if (OtherActor)
	{
		// log message for debugging
		UE_LOG(LogTemp, Warning, TEXT("Box overlapped with actor: %s"), *OtherActor->GetName());
		//print message in screen
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("overlapped outside"));
	}
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, .0f, FColor::Red, TEXT("outside"));

	//UWorld::SpawnActor();
	//UClass* ActorClassToSpawn = LightSwitchBoth::StaticClass();
	//FTransform SpawnTransform = FTransform::Identity; // Set your desired transform
	//AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorClassToSpawn, SpawnTransform);
}

