// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

//world stuff
#include "Kismet/GameplayStatics.h"


//Widgets
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "MyHud.h"
#include "MyStartButton.h"

void AMyPlayerController::BeginPlay()
{
	if (HudAsset != nullptr) {
		Hud = CreateWidget<UMyHud>(GetWorld(), HudAsset);
		Hud->AddToViewport();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Hud Asset selected"));
	}
	if (HudAsset != nullptr) {
		StartButton = CreateWidget<UMyStartButton>(GetWorld(), StartButtonAsset);
		StartButton->AddToViewport();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No StartButtonSelected"));
	}
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this);
	bShowMouseCursor = true;
}

