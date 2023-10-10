// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyStartButton.generated.h"

/**
 * 
 */

 class UButton;
UCLASS()
class PILOTBLADES_API UMyStartButton : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* BTN_Start;

	UFUNCTION()
	void onStartClicked();
	
};
