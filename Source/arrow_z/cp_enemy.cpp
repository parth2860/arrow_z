// Fill out your copyright notice in the Description page of Project Settings.


#include "cp_enemy.h"
#include "arrow_zCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
//#include "Perception/PawnSensingComponent.h"
// Sets default values
Acp_enemy::Acp_enemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//--------------------------------------------------------------------------------------------------------------
	//sensing component
	//SensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("SensingComponent"));
	//SensingComponent->SetSensingInterval(0.5f); // Sensing every half second

	//SensingComponent->OnHearNoise.AddDynamic(this, &AYourCharacter::OnHearNoise);
	//SensingComponent->OnSeePawn.AddDynamic(this, &AYourCharacter::OnSeePawn);
	//--------------------------------------------------------------------------------------------------------------
	enemy_weapon_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("enemy_Weapon_mesh"));
	//Weapon_mesh->SetupAttachment(GetMesh(), TEXT("enemy_weapon"));
	enemy_weapon_mesh->SetupAttachment(RootComponent);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/assets/3d_mesh/Sword.Sword'"));//D:/Users/PARTH/Documents/Unreal Projects/c++/arrow_z/Content/assets/3d_mesh/Sword.uasset
	if (MeshAsset.Succeeded())
	{
		enemy_weapon_mesh->SetStaticMesh(MeshAsset.Object);
	}

	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
}

// Called when the game starts or when spawned
void Acp_enemy::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void Acp_enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    follow_player();
}

// Called to bind functionality to input
void Acp_enemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
//--------------------------------------------------------------------------------------------------------------
void Acp_enemy::OnSeePawn(APawn* OtherPawn)
{
	// Get the player's pawn
	Aarrow_zCharacter* player = Cast<Aarrow_zCharacter>(OtherPawn);
	if (player)
	{
		// Calculate the direction from enemy to player
		FVector Direction = player->GetActorLocation() - GetActorLocation();
		Direction.Normalize();

		// Rotate the enemy to face the player
		FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
		NewLookAt.Pitch = 0;
		NewLookAt.Roll = 0;
		SetActorRotation(NewLookAt);
	}

}
//--------------------------------------------------------------------------------------------------------------
void Acp_enemy::enemy_takeDamage(float DamageAmount)
{
	CurrentHealth -= DamageAmount;
	if (CurrentHealth <= 0)
	{
		enemy_death();
	}

}
void Acp_enemy::enemy_death()
{
	PlayAnimMontage(ed_1);
}

void Acp_enemy::follow_player()
{
	Aarrow_zCharacter* player = Cast<Aarrow_zCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));//targrt player
	float FollowDistance = 200.0f;

	if (player)
	{
		FVector Direction = player->GetActorLocation() - GetActorLocation();
		float Distance = Direction.Size();//enemy keep distance

		if (Distance > FollowDistance)
		{
			Direction.Normalize();
			AddMovementInput(Direction, 1.0f);

			// Set enemy rotation to face the player
			FRotator NewRotation = Direction.Rotation();
			NewRotation.Pitch = 0.0f; // Keep pitch level to avoid tilting up or down
			NewRotation.Roll = 0.0f;  // Keep roll level to avoid tilting sideways
			SetActorRotation(NewRotation);

		}
		else
		{
			// Stop the enemy from moving towards the player
			//AddMovementInput(FVector::ZeroVector, 1.0f);
			attack();
		}
	}
	/*
	if (player)
	{
		FVector Direction = player->GetActorLocation() - GetActorLocation();
		Direction.Normalize();
		AddMovementInput(Direction, 1.0f);
	}*/
}
void Acp_enemy::attack()
{
	//PlayAnimMontage(ea_1);

	if (!GetMesh()->IsPlayingRootMotion())
	{
		GetMesh()->GetAnimInstance()->Montage_Play(ea_1, 1.0f);
	}
}

