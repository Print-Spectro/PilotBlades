// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMyInterface : public UInterface
{
	GENERATED_BODY()
};

class PILOTBLADES_API IMyInterface
{
	GENERATED_BODY()

public:
	virtual void pickUp(float FuelAmount) {};

	virtual void setFuel(float FuelAmount) {};

	virtual void win() {};
};
