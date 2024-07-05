// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "cp_enemy.generated.h"

UCLASS()
class ARROW_Z_API Acp_enemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	Acp_enemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//--------------------------------------------------------------------------------------------------------------
	//basic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "enemy weapon")
	UStaticMeshComponent* enemy_weapon_mesh;

	// Health properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	float CurrentHealth;

	// Damage function
	UFUNCTION(BlueprintCallable, Category = "enemy_damage")
	void enemy_takeDamage(float DamageAmount);
	//death animation
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "enemy_damage")
	UAnimMontage* ed_1;
	void enemy_death();
	//--------------------------------------------------------------------------------------------------------------
	//ai component
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sensing")
	//class UPawnSensingComponent* SensingComponent;

	//UFUNCTION()
	//void OnHearNoise(APawn* OtherActor, const FVector& Location, float Volume);

	UFUNCTION()
	void OnSeePawn(APawn* OtherPawn);

	//--------------------------------------------------------------------------------------------------------------
	//attack
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "enemy_c1")
	UAnimMontage* ea_1;

	UFUNCTION()
	void follow_player();
	void attack();
	
	
	
};
