// Fill out your copyright notice in the Description page of Project Settings.


#include "cp_bullets.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
Acp_bullets::Acp_bullets()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//-----------------------------------------------------------------------------------------------
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &Acp_bullets::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 9.0f;

	bullets= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("bullets"));
	bullets->SetupAttachment(RootComponent);
	//gun_mesh->
	//
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/assets/3d_mesh/bullet-mesh.bullet-mesh'"));// /arrow_z/Content/assets/3d_mesh/bullet-mesh.uasset
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/LevelPrototyping/Meshes/SM_Cylinder.SM_Cylinder'"));
	if (MeshAsset.Succeeded())
	{
		bullets->SetStaticMesh(MeshAsset.Object);
		bullets->SetRelativeScale3D(FVector(0.05f, 0.01f, 0.01f));//size of bullets
	}//

}

// Called when the game starts or when spawned
void Acp_bullets::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Acp_bullets::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void Acp_bullets::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Hit"));
	}
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("2nd Hit"));
}

