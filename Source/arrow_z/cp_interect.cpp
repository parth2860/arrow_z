// Fill out your copyright notice in the Description page of Project Settings.


#include "cp_interect.h"
//#include "Components/BoxComponent.h"

// Sets default values
Acp_interect::Acp_interect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//box_area = CreateDefaultSubobject<UBoxComponent>(TEXT("box_area"));
	//BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	//RootComponent = BoxCollision;
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

