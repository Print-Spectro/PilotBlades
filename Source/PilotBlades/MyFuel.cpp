// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFuel.h"

//CollisionSphere
#include "Components/SphereComponent.h"

//interface
#include "MyInterface.h"

#include "Kismet/GameplayStatics.h"

#include "Sound/SoundBase.h"

// Sets default values
AMyFuel::AMyFuel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = Mesh;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));

	CollisionSphere->SetupAttachment(Mesh);

	CollisionSphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &AMyFuel::onOverlap);
}

// Called when the game starts or when spawned
void AMyFuel::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyFuel::onOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IMyInterface* Interface = Cast<IMyInterface>(OtherActor)) {
		Interface->pickUp(Fuel);
		if (PickupSoundEffect) {
			UGameplayStatics::PlaySoundAtLocation(this, PickupSoundEffect, GetActorLocation());
			UE_LOG(LogTemp, Warning, TEXT("AMyFuel::onOverlap: No Pickup sound effect selected"));
		}
		
		Destroy();
	}
	UE_LOG(LogTemp, Warning, TEXT("AMyFuel::onOverlap: Cast to IMyInterface failed"));
}

// Called every frame
void AMyFuel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



