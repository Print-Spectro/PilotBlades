// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLandingPad.h"

//CollisionSphere
#include "Components/SphereComponent.h"

//interface
#include "MyInterface.h"

// Sets default values
AMyLandingPad::AMyLandingPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = Mesh;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));

	CollisionSphere->SetupAttachment(Mesh);

	CollisionSphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &AMyLandingPad::onOverlap);

}

// Called when the game starts or when spawned
void AMyLandingPad::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyLandingPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyLandingPad::onOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IMyInterface* Interface = Cast<IMyInterface>(OtherActor)) {
		Interface->win();

	}
}

