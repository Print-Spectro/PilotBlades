// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLandingPad.h"

//CollisionSphere
#include "Components/SphereComponent.h"

//interface
#include "MyInterface.h"

// Sets default values
AMyLandingPad::AMyLandingPad()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	CollisionSphere->SetupAttachment(Mesh);
	CollisionSphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &AMyLandingPad::onOverlap);
}

void AMyLandingPad::onOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IMyInterface* Interface = Cast<IMyInterface>(OtherActor)) {
		Interface->win();
	}
}

