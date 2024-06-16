// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "cp_player_interface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class Ucp_player_interface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARROW_Z_API Icp_player_interface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void EquipWeapon();
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "interface")//Blueprint callable interface functions cannot be virtual.
	//void EquipWeapon();
	
	virtual bool ReactToTrigger();

	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "interface")
	//bool ReactToTrigger();
};
