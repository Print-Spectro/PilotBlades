// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHud.h"

//Widget Components
#include "Components/TextBlock.h"



void UMyHud::NativeConstruct()
{
	SetFuel(420);
}

void UMyHud::SetFuel(const float Value)
{
	Text_Fuel->SetText(FText::FromString(FString::Printf(TEXT("%f"), Value)));
}

void UMyHud::setFuel(float amount)
{
	SetFuel(amount);
}
