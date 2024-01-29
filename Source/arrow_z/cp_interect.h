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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/* 
	UPROPERTY(VisibleAnywhere, Category = "Box Components")
		class BoxComponent* box_area;
	UPROPERTY(VisibleAnywhere, Category = "Box Components")
		class BoxComponent* BoxCollision;*/
};
