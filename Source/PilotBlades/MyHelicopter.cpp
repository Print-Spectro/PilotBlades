// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHelicopter.h"

//input mapping 
#include "MyInputConfigData.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include "EnhancedInput/Public/EnhancedInputComponent.h"


//components 
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMyHelicopter::AMyHelicopter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = Mesh;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));//Creating spring arm
	SpringArmComp->SetupAttachment(Mesh);//Setting up attachment to the mesh


	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	ThirdPersonCamera->SetupAttachment(SpringArmComp);

}

// Called when the game starts or when spawned
void AMyHelicopter::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void AMyHelicopter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyHelicopter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Get player controller
	APlayerController* PC = Cast<APlayerController>(GetController());

	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

	//Clear out existing mapping, and add our mapping
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	//Getting the EnhancedInputComponent
	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	//Binding the actions
	//PEI->BindAction(InputActions->InputSteer, ETriggerEvent::Triggered, this, &AMyHelicopter::setThrottle);
	//PEI->BindAction(InputActions->InputSteer, ETriggerEvent::Completed, this, &AMyHelicopter::setThrottle);
	PEI->BindAction(InputActions->InputLook, ETriggerEvent::Triggered, this, &AMyHelicopter::Look);

}

void AMyHelicopter::setThrottle()
{
}

void AMyHelicopter::Look(const FInputActionValue& Value) {
	FVector2D LookValue = Value.Get<FVector2D>();
	//UE_LOG(LogTemp, Log, TEXT("LOOK"));
	if (Controller != nullptr) {
		//UE_LOG(LogTemp, Log, TEXT("Controller"));
		AddControllerYawInput(LookValue.X);
		AddControllerPitchInput(LookValue.Y);
	}
}
