// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHud.h"
//Widget Components
#include "Components/TextBlock.h"


void UMyHud::SetFuel(float Value)
{
	if (Text_Fuel) {
		Text_Fuel->SetText(FText::FromString(FString::Printf(TEXT("%.2f"), Value)));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("UMyHud::SetFuel: No text to bind"))
	}
}

void UMyHud::setFuel(float amount)
{
	SetFuel(amount);
}
