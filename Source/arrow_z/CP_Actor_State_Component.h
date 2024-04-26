// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CP_Actor_State_Component.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARROW_Z_API UCP_Actor_State_Component : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCP_Actor_State_Component();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
    // Health
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
    float Health;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
    float MaxHealth;

    // Stamina
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
    float Stamina;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
    float MaxStamina;

    // Level
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
    int32 CurrentLevel;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
    int32 MaxLevel;

    // Functions
    UFUNCTION(BlueprintCallable)
    void IncreaseHealth(float Amount);

    UFUNCTION(BlueprintCallable)
    void DecreaseHealth(float Amount);

    UFUNCTION(BlueprintCallable)
    void IncreaseStamina(float Amount);

    UFUNCTION(BlueprintCallable)
    void DecreaseStamina(float Amount);

    UFUNCTION(BlueprintCallable)
    void LevelUp();

};
