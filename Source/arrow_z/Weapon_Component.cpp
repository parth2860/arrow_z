// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Component.h"

// Sets default values for this component's properties
UWeapon_Component::UWeapon_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeapon_Component::BeginPlay()
{
	Super::BeginPlay();

	// ...
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Yellow, TEXT("component"));
}


// Called every frame
void UWeapon_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

