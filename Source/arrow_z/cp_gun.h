// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "cp_gun.generated.h"

UCLASS()
class ARROW_Z_API Acp_gun : public AActor 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Acp_gun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//-----------------------------------------------------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "weapon")
	UStaticMeshComponent* gun_mesh;
	//UPROPERTY()
	//UStaticMesh* gun_mesh_asset;
	
	UPROPERTY()
	class USphereComponent* CollisionComp;

	bool isequiped;
	

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable, Category = "fire")
	void fire();

};
