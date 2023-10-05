// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "Blueprint/WidgetBlueprintLibrary.h"

#include "MyHud.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();


	if (MainMenuAsset != nullptr) {
		Hud = CreateWidget<UMyHud>(GetWorld(), MainMenuAsset);

		Hud->AddToViewport();

		//UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this);
		//bShowMouseCursor = true;

		//WidgetSwitcherInst = MenuSwitchInst->WidgetSwitcher;

	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Menu Switcher Widget Selected"));
	}
}

