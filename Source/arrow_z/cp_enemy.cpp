// Fill out your copyright notice in the Description page of Project Settings.


#include "cp_enemy.h"

// Sets default values
Acp_enemy::Acp_enemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

}

// Called to bind functionality to input
void Acp_enemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void Acp_enemy::follow_player()
{
	
}
void Acp_enemy::attack()
{
	PlayAnimMontage(ea_1);
}

