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

};
