// Fill out your copyright notice in the Description page of Project Settings.


#include "cp_bullets.h"

// Sets default values
Acp_bullets::Acp_bullets()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

