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
#include "PhysicsEngine/PhysicsThrusterComponent.h"

//hud and that
#include "MyPlayerController.h"
#include "MyHud.h"


//debug
#include "DrawDebugHelpers.h"

// Sets default values
AMyHelicopter::AMyHelicopter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = Mesh;


	Blades = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Blades"));
	Blades->SetupAttachment(Mesh);

	Thruster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("Thruster"));
	Thruster->SetupAttachment(Mesh);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));//Creating spring arm
	SpringArmComp->SetupAttachment(Mesh);//Setting up attachment to the mesh


	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	ThirdPersonCamera->SetupAttachment(SpringArmComp);



}

// Called when the game starts or when spawned
void AMyHelicopter::BeginPlay()
{
	Super::BeginPlay();
	
	FVector ThrustCenterOfMassDiff = Thruster->GetComponentLocation() - Mesh->GetCenterOfMass();
	FRotator InverseMeshRotation = Mesh->GetComponentRotation().GetInverse();

	FVector CenterOfMassOffset = InverseMeshRotation.RotateVector(ThrustCenterOfMassDiff);
	//Shifting in xy plane
	FVector CenterOfMassDesiredOffset = FVector(CenterOfMassOffset.X, CenterOfMassOffset.Y, 0);
	Mesh->SetCenterOfMass(CenterOfMassDesiredOffset, "None");

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	MyPlayerController = Cast<AMyPlayerController>(PlayerController);
}




// Called every frame
void AMyHelicopter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Mesh->SetSimulatePhysics(true);
	//aligning centre of mass with thruster 

	Fuel -= FuelUse*DeltaTime;
	//UE_LOG(LogTemp, Display, TEXT("Fuel %f"), Fuel);
	if (MyPlayerController && Fuel > 0) {
		MyPlayerController->Hud->setFuel(Fuel);
	}

	Blades->AddRelativeRotation(FRotator(0,90,0)*DeltaTime);
}

// Called to bind functionality to input
void AMyHelicopter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Get player controller
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("AMyHelicopter::SetupPlayerInputComponent: No PlayerController found"));
	}

	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

	if (InputMapping == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("AMyHelicopter::SetupPlayerInputComponent: No InputMapping selected"));
		return;
	}
	if (InputActions == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("AMyHelicopter::SetupPlayerInputComponent: No InputConfigData set"));
		return;
	}

	//Clear out existing mapping, and add our mapping
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	//Getting the EnhancedInputComponent
	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	//Binding the actions
	//PEI->BindAction(InputActions->InputSteer, ETriggerEvent::Triggered, this, &AMyHelicopter::setThrottle);
	//PEI->BindAction(InputActions->InputSteer, ETriggerEvent::Completed, this, &AMyHelicopter::setThrottle);
	PEI->BindAction(InputActions->InputLook, ETriggerEvent::Triggered, this, &AMyHelicopter::Look);
	PEI->BindAction(InputActions->InputTilt, ETriggerEvent::Triggered, this, &AMyHelicopter::Tilt);
	PEI->BindAction(InputActions->InputTilt, ETriggerEvent::Completed, this, &AMyHelicopter::Tilt);
	PEI->BindAction(InputActions->InputTurn, ETriggerEvent::Triggered, this, &AMyHelicopter::Rotate);
	//PEI->BindAction(InputActions->InputTurn, ETriggerEvent::Completed, this, &AMyHelicopter::Rotate);
	PEI->BindAction(InputActions->InputAccelerate, ETriggerEvent::Triggered, this, &AMyHelicopter::MoveUp);
	PEI->BindAction(InputActions->InputAccelerate, ETriggerEvent::Completed, this, &AMyHelicopter::MoveUp);
}

void AMyHelicopter::pickUp(float FuelAmount)
{
	AddFuel(FuelAmount);
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

void AMyHelicopter::MoveUp(const FInputActionValue& Value)
{	
	
	float ThrottleValue = Value.Get<float>();
	float Force = ThrottleValue * ActiveThrust + PassiveThrust;
	float UpVectorClamped = FMath::Clamp(GetActorUpVector().Z, TiltThrustAssistThreshold, 1);
	if (Fuel <= 0) {
		Force = 0;
	}
	Thruster->ThrustStrength = Force / UpVectorClamped * Mesh->GetMass();
	FuelUse = ThrottleValue*ActiveFuelUse + LatentFuelUse;
	UE_LOG(LogTemp, Warning, TEXT("Thrust %f"), Force / UpVectorClamped * Mesh->GetMass());
}

void AMyHelicopter::Tilt(const FInputActionValue& Value)
{
	if (Fuel <= 0) return;
	FVector2D TiltInput = Value.Get<FVector2D>();
	float Angle = TiltInput.Y * TiltAngle + Mesh->GetComponentRotation().Pitch;
	float ClampedAngle = FMath::Clamp(Angle, -TiltSpeedClamp, TiltSpeedClamp);
	if (Fuel <= 0) {
		TiltSpeed = 0;
	}
	Mesh->AddTorqueInDegrees(GetActorRightVector() * ClampedAngle * TiltSpeed, "None", true);

	
	float Angle2 = TiltInput.X * TiltAngle + Mesh->GetComponentRotation().Roll;
	float ClampedAngle2 = FMath::Clamp(Angle2, -TiltSpeedClamp, TiltSpeedClamp);
	Mesh->AddTorqueInDegrees(GetActorForwardVector() * ClampedAngle2 * TiltSpeed, "None", true);
}

void AMyHelicopter::Rotate(const FInputActionValue& Value)
{	
	if (Fuel <= 0) return;
	float TurnInput = Value.Get<float>();
	//UE_LOG(LogTemp, Warning, TEXT("%f"), TurnInput);
	Mesh->AddTorqueInDegrees(GetActorUpVector() * TurnInput * TurnRate, "None", true);
}

void AMyHelicopter::AddFuel(float amount)
{
	Fuel += amount;
}

void AMyHelicopter::win()
{
	
}

