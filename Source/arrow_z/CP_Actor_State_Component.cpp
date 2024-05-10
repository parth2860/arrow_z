// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_Actor_State_Component.h"

// Sets default values for this component's properties
UCP_Actor_State_Component::UCP_Actor_State_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	//--------------------------------------------------------------------------
	// Set default values
	Health = MaxHealth = 100.0f;
	Stamina = MaxStamina = 100.0f;
	CurrentLevel = 1;
	MaxLevel = 10;
}


// Called when the game starts
void UCP_Actor_State_Component::BeginPlay()
{
	Super::BeginPlay();

	// ...
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Yellow, TEXT("component"));
}


// Called every frame
void UCP_Actor_State_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Yellow, TEXT("component"));
}
//--------------------------------------------------------------------------
void UCP_Actor_State_Component::IncreaseHealth(float Amount)
{
	Health = FMath::Clamp(Health + Amount, 0.0f, MaxHealth);
}

void UCP_Actor_State_Component::DecreaseHealth(float Amount)
{
	Health = FMath::Clamp(Health - Amount, 0.0f, MaxHealth);
}

void UCP_Actor_State_Component::IncreaseStamina(float Amount)
{
	Stamina = FMath::Clamp(Stamina + Amount, 0.0f, MaxStamina);
}

void UCP_Actor_State_Component::DecreaseStamina(float Amount)
{
	Stamina = FMath::Clamp(Stamina - Amount, 0.0f, MaxStamina);
}

void UCP_Actor_State_Component::LevelUp()
{
	if (CurrentLevel < MaxLevel)
	{
		CurrentLevel++;
	}
}

