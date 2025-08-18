// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "_Game/UI/Widget/MVCWidget.h"
#include "_Game/UI/WidgetController/OverlayController.h"
#include "MVCHUD.generated.h"


/**
 * 
 */
UCLASS()
class GAS_API AMVCHUD : public AHUD
{
	GENERATED_BODY()

public:
	
	UPROPERTY()
	TObjectPtr<UMVCWidget> OverlayWidget;

	UOverlayController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	void InitPrimary(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	
private:

	UPROPERTY()
	TObjectPtr<UOverlayController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayController> OverlayWidgetControllerClass;
};
