// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/UI/Widget/MVCWidget.h"

void UMVCWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet_Event();

}
