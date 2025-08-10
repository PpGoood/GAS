// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/UI/WidgetController/MVCController.h"

void UMVCController::SetWidgetControllerParmas(const FWidgetControllerParams& Params)
{
	PlayerController = Params.PlayerController;
	PlayerState = Params.PlayerState;
	AbilitySystemComponent = Params.AbilitySystemComponent;
	AttributeSet = Params.AttributeSet;
}
