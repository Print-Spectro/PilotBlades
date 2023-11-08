// Fill out your copyright notice in the Description page of Project Settings.


#include "MyStartButton.h"

//Button
#include "Components/Button.h"

//unpause game
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UMyStartButton::NativeConstruct()
{
	if (BTN_Start) {
		BTN_Start->OnClicked.AddDynamic(this, &UMyStartButton::onStartClicked);
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("UMyStartButton::NativeConstruct: No Start button to bind"))
	}
}

void UMyStartButton::onStartClicked()
{
	UGameplayStatics::SetGamePaused(GetWorld(), 0);
	RemoveFromViewport();
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor  = false;
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController());
}


