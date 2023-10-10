// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PILOTBLADES_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	

	virtual void BeginPlay() override;

	public:

	UPROPERTY(EditDefaultsOnly, category = "Widget")
	TSubclassOf<UUserWidget> HudAsset;

	UPROPERTY(EditDefaultsOnly, category = "Widget")
	TSubclassOf<UUserWidget> StartButtonAsset;

	UPROPERTY()
	class UMyHud* Hud;

	UPROPERTY()
	class UMyStartButton* StartButton;

};
