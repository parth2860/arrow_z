// Fill out your copyright notice in the Description page of Project Settings.


#include "cp_gun.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

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


}

// Called when the game starts or when spawned
void Acp_gun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Acp_gun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void Acp_gun::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap"));
}
void Acp_gun::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("End Overlap"));
}
