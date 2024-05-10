// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Component.h"

// Sets default values for this component's properties
UWeapon_Component::UWeapon_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	// Initialize EquippedWeaponIndex to -1 (no weapon equipped)
	EquippedWeaponIndex = -1;
}


// Called when the game starts
void UWeapon_Component::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("component"));
}


// Called every frame
void UWeapon_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
void UWeapon_Component::weapon_inventory()
{
}

void UWeapon_Component::AddWeapon(AActor* WeaponToAdd)
{
	// Add the weapon to the inventory
	Weapons.Add(WeaponToAdd);
}

void UWeapon_Component::RemoveWeapon(AActor* WeaponToRemove)
{
	// Remove the weapon from the inventory
	Weapons.Remove(WeaponToRemove);
}

void UWeapon_Component::EquipWeapon(int32 WeaponIndex)
{
	// Check if the requested weapon index is valid
	if (WeaponIndex >= 0 && WeaponIndex < Weapons.Num())
	{
		// Deactivate the currently equipped weapon
		if (EquippedWeaponIndex >= 0 && EquippedWeaponIndex < Weapons.Num())
		{
			// Switch the currently equipped weapon to its original slot (assuming HeldSocket and BackSocket exist)
			// You may need to implement functionality to handle this based on your specific setup
		}

		// Equip the new weapon
		EquippedWeaponIndex = WeaponIndex;

		// Activate the new weapon
		// You may need to implement functionality to handle this based on your specific setup
	}
}

