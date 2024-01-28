// Fill out your copyright notice in the Description page of Project Settings.

//#include "arrow_z.h"
#include "LightSwitchBoth.h"
#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ALightSwitchBoth::ALightSwitchBoth()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    //create point light component
    DesiredIntensity = 7000.0f;

    PointLight1 = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight1"));
    PointLight1->Intensity = DesiredIntensity;
   // PointLight1->bVisible = true;
    PointLight1->SetVisibility(true);
    RootComponent = PointLight1;

    //create sphere component
    Sphere1 = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere1"));
    Sphere1->InitSphereRadius(250.0f);
    Sphere1->SetupAttachment(RootComponent);

    Sphere1->OnComponentBeginOverlap.AddDynamic(this, &ALightSwitchBoth::OnOverlapBegin);       // set up a notification for when this component overlaps something
    Sphere1->OnComponentEndOverlap.AddDynamic(this, &ALightSwitchBoth::OnOverlapEnd);       // set up a notification for when this component overlaps something
}

// Called when the game starts or when spawned
void ALightSwitchBoth::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALightSwitchBoth::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ALightSwitchBoth::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        ToggleLight();
    }
    //print essage in screen
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("light off"));
}

void ALightSwitchBoth::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        ToggleLight();
    }
}

void ALightSwitchBoth::ToggleLight()
{
    PointLight1->ToggleVisibility();
}


