// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "cp_exp.generated.h"

UCLASS()
class OP_WORLD_API Acp_exp : public AActor
{
	GENERATED_BODY()
	
public:	

	/** Please add a variable description */
	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	//	TObjectPtr<URotatingMovementComponent> RotatingMovement;

	/** Please add a variable description */
	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
		//TObjectPtr<UStaticMeshComponent> Cylinder;
	/** Please add a variable description */
	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	//	TObjectPtr<USceneComponent> DefaultSceneRoot;
	//// Corrected member variable declaration
	//UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Default")
	//	UStaticMeshComponent* Cylinder;
	

	//----------------------------------------------------
	
	//----------------------------------------------------

	// Sets default values for this actor's properties
	Acp_exp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	// Function to set the rotation speed of the sphere
	UFUNCTION(BlueprintCallable, Category = "Rotation")
		void SetRotationSpeed(float Speed, float DeltaTime);
protected:
	// Sphere mesh component
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Default")
		UStaticMeshComponent* SphereMesh;

	// Speed at which the sphere rotates
	float RotationSpeed;
};

