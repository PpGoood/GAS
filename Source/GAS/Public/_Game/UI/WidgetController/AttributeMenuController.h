// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "_Game/UI/WidgetController/MVCController.h"
#include "AttributeMenuController.generated.h"

/**
 * 
 */
UCLASS()
class GAS_API UAttributeMenuController : public UMVCController
{
	GENERATED_BODY()
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
};
