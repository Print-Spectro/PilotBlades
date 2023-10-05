// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyHelicopter.generated.h"

UCLASS()
class PILOTBLADES_API AMyHelicopter : public APawn
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


	UFUNCTION()
	void setThrottle();

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void MoveUp(const FInputActionValue& Value);

	UFUNCTION()
	void Tilt(const FInputActionValue& Value);

	UFUNCTION()
	void Rotate(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
