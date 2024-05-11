// Fill out your copyright notice in the Description page of Project Settings.


#include "cp_gun.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "arrow_zCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "cp_bullets.h"

// Sets default values
Acp_gun::Acp_gun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//-----------------------------------------------------------------------------------------------
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(50.0f);
	//CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &Acp_gun::OnBeginOverlap);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &Acp_gun::OnEndOverlap);
	
	RootComponent = CollisionComp;

	gun_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("gun_mesh"));
	gun_mesh->SetupAttachment(RootComponent);
	//gun_mesh->
	//
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/assets/3d_mesh/wepon_pack/wepon_pack_hand_gun.wepon_pack_hand_gun'"));
	if (MeshAsset.Succeeded())
	{
		gun_mesh->SetStaticMesh(MeshAsset.Object);
	}//

	isequiped;
	
}

// Called when the game starts or when spawned
void Acp_gun::BeginPlay()
{
	Super::BeginPlay();
	// Register our Overlap Event
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &Acp_gun::OnBeginOverlap);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &Acp_gun::OnEndOverlap);
}

// Called every frame
void Acp_gun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
void Acp_gun::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Overlap"));
	Aarrow_zCharacter* player = Cast<Aarrow_zCharacter>(OtherActor);
	//FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTargetNotIncludingScale, true);//error
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);//once attch overlap event run every frame
	//AttachToActor(player->cp_gun, FAttachmentTransformRules::SnapToTargetNotIncludingScale);//{FAttachmentTransformRules::SnapToTargetNotIncludingScale}//once attach it trigger once
	//AttachToComponent(player->cp_gun, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(TEXT("gun_socket")));//once it crashed////overlap/end begin trigger one time
	gun_mesh->AttachToComponent(player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(TEXT("gun_socket")));//attch to dedicated socket but,it restrict  create new mesh for new weapon
	//gun_mesh->AttachToComponent(player->cp_gun, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(TEXT("gun_socket")));//overlap/end begin trigger many time
	gun_mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);//remove collision

	// Unregister from the Overlap Event so it is no longer triggered
	CollisionComp->OnComponentBeginOverlap.RemoveAll(this);//eliminate triggering event
	
	 isequiped = true;
	

}
void Acp_gun::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("End Overlap"));

	// Unregister from the Overlap Event so it is no longer triggered
	CollisionComp->OnComponentEndOverlap.RemoveAll(this);//eliminate triggering event
}
void Acp_gun::fire()
{
	//Aarrow_zCharacter* player = Cast<Aarrow_zCharacter>(UGameplayStatics::GetActorOfClass(Aarrow_zCharacter::StaticClass(), 0));

	if (isequiped == true)
	{
		// Get a reference to the game world
		UWorld* World = GetWorld();
		if (World)
		{
			
			FVector loc = gun_mesh->GetSocketLocation("muzzle_socket");
			FRotator rot = gun_mesh->GetSocketRotation("muzzle_socket");
			//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("socket location : %s"), loc);

			// Define the spawn parameters (location, rotation, etc.)
			FVector SpawnLocation(0.f, 0.f, 100.f); // Example spawn location
			FRotator SpawnRotation(0.f, 0.f, 0.f); // Example spawn rotation
			FActorSpawnParameters SpawnParams;

			// Spawn the actor from the specified class
			Acp_bullets* SpawnedActor = World->SpawnActor<Acp_bullets>(Acp_bullets::StaticClass(), loc, rot, SpawnParams);

			// Check if the actor was successfully spawned
			if (SpawnedActor)
			{
				// Optionally, perform additional initialization or manipulation of the spawned actor
				// For example, you can set properties, attach to other actors, etc.
				UE_LOG(LogTemp, Error, TEXT(" spawn actor from class AYourActorClass."));

			}
			else
			{
				// Handle error if actor spawning failed
				UE_LOG(LogTemp, Error, TEXT("Failed to spawn actor from class AYourActorClass."));
			}
		}
		else
		{
			// Handle error if world reference is invalid
			UE_LOG(LogTemp, Error, TEXT("World reference is null. Unable to spawn actor."));
		}


	}
}