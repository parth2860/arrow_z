// Fill out your copyright notice in the Description page of Project Settings.


#include "cp_interect.h"
#include "Components/BoxComponent.h"

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

	// Bind the overlap function to the OnComponentBeginOverlap event
	MyBoxCollision->OnComponentBeginOverlap.AddDynamic(this, &Acp_interect::OnBoxOverlap);

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
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("overlapped"));
	}
}

