// Fill out your copyright notice in the Description page of Project Settings.


#include "cp_projectile.h"

// Sets default values
Acp_projectile::Acp_projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Acp_projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Acp_projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

