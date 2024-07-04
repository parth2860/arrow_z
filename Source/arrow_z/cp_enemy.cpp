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
	PlayAnimMontage(ea_1);
}

