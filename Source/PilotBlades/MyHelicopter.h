// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//interface
#include "MyInterface.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyHelicopter.generated.h"


UCLASS()
class PILOTBLADES_API AMyHelicopter : public APawn, public IMyInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyHelicopter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite);
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite);
	class UStaticMeshComponent* Blades;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite);
	class UPhysicsThrusterComponent* Thruster;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	class UMyInputConfigData* InputActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UCameraComponent* ThirdPersonCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Helicopter Parameters")
	float ActiveThrust = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Helicopter Parameters")
	float PassiveThrust = 970;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Helicopter Parameters")
	float TiltThrustAssistThreshold = 0.5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Helicopter Parameters")
	float TiltAngle = 30;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Helicopter Parameters")
	float TiltSpeedClamp = 20;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Helicopter Parameters")
	float TiltSpeed = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Helicopter Parameters")
	float TurnRate = 60;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Helicopter Parameters")
	float StartFuel = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Helicopter Parameters")
	float Fuel = StartFuel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Helicopter Parameters")
	float BladeRotationRate = 2;

	//Setting fuel usage high or low
	UPROPERTY()
	float FuelUse = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Helicopter Parameters")
	float LatentFuelUse = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Helicopter Parameters")
	float ActiveFuelUse = 1;

	UFUNCTION()
	void restartLevel();

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void SetThrottle(const FInputActionValue& Value);

	UFUNCTION()
	void Tilt(const FInputActionValue& Value);

	UFUNCTION()
	void Rotate(const FInputActionValue& Value);

	UFUNCTION()
	void AddFuel(float amount);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void pickUp(float FuelAmount) override;

	virtual void win() override;

	UPROPERTY()
	class AMyPlayerController* MyPlayerController;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bInvertLook = 0;
};
