// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
//#include "arrow_zCharacter.h"
#include "Weapon_Component.generated.h"

//class arrow_zCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARROW_Z_API UWeapon_Component : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeapon_Component();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//-----------------------------------------------------------------------------------------------
	// Array to hold references to the weapons in the inventory
	UPROPERTY()
	TArray<AActor*> Weapons;

	// Index of the currently equipped weapon
	int32 EquippedWeaponIndex;

	UFUNCTION(BlueprintCallable , Category = "weapon component")
	void weapon_inventory();

	// Function to add a weapon to the inventory
	void AddWeapon(AActor* WeaponToAdd);

	// Function to remove a weapon from the inventory
	void RemoveWeapon(AActor* WeaponToRemove);

	// Function to equip a weapon from the inventory
	void EquipWeapon(int32 WeaponIndex);
};
