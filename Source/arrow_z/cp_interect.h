// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "cp_interect.generated.h"

UCLASS()
class ARROW_Z_API Acp_interect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Acp_interect();

	// Declare the delegate
	//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBeginOverlap);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/* 
	UPROPERTY(VisibleAnywhere, Category = "Box Components")
		class UBoxComponent* box_area = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Box Components")
		class UBoxComponent* BoxCollision;//boxcompontent//absent of class
	*/
	//box collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		class UBoxComponent* MyBoxCollision = nullptr;

	UFUNCTION()
		void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		//void OnBoxOverlapend(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	    //void OnBoxOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	    void OnBoxOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	//static mesh
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UStaticMeshComponent* mesh_plane;
	// arrow
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Arrow")





		class UArrowComponent* arrow;
};
