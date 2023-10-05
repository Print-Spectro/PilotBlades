// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyInterface.h"

#include "MyHud.generated.h"

/**
 * 
 */
 class UTextBlock;

UCLASS()
class PILOTBLADES_API UMyHud : public UUserWidget, public IMyInterface
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;

public:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* Text_Fuel;

	UFUNCTION()
	void SetFuel(const float Value);


	virtual void setFuel(float amount) override;


};
