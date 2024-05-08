// Fill out your copyright notice in the Description page of Project Settings.


#include "cp_gun.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "arrow_zCharacter.h"

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
	AttachToComponent(player->cp_gun, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(TEXT("gun_socket")));//once it crashed////overlap/end begin trigger one time
	//gun_mesh->AttachToComponent(player->cp_gun, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(TEXT("gun_socket")));//overlap/end begin trigger many time
	gun_mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);//remove collision

	// Unregister from the Overlap Event so it is no longer triggered
	CollisionComp->OnComponentBeginOverlap.RemoveAll(this);//eliminate triggering event
	
	

}
void Acp_gun::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("End Overlap"));

	// Unregister from the Overlap Event so it is no longer triggered
	CollisionComp->OnComponentEndOverlap.RemoveAll(this);//eliminate triggering event
}
