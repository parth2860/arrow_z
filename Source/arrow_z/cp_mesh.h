// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "cp_mesh.generated.h"

UCLASS()
class ARROW_Z_API Acp_mesh : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Acp_mesh();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every framecs
	virtual void Tick(float DeltaTime) override;

	
//protected:
	 //UPROPERTY(Category = Meshes, VisibleAnywhere)
	 // class TSubobjectPtr<UStaticMeshComponent> CubeMesh;

	 UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Default")
	 UStaticMeshComponent* SphereMesh;
	 
	 float RotationSpeed;

	 // Function to set the rotation speed of the sphere
	 UFUNCTION(BlueprintCallable, Category = "Rotation")
	 void SetRotationSpeed(float Speed, float DeltaTime);

	 UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	 class UBoxComponent* BoxCollisionarea = nullptr;

	 UFUNCTION()
	 void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	 UFUNCTION()
	  void OnBoxOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
