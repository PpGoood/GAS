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
	
	// UPROPERTY()
	// TObjectPtr<UMVCWidget> OverlayWidget;

	// UOverlayController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	void InitControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	UFUNCTION(BlueprintCallable)
	UCommonActivatableWidget* OpenUI(FGameplayTag WidgetClassTag);
	UFUNCTION(BlueprintCallable)
	void CloseUI(FGameplayTag WidgetClassTag);

	UFUNCTION(BlueprintCallable)
	UCommonActivatableWidget* OpenUIByString(FString& WidgetClassString);
	UFUNCTION(BlueprintCallable)
	void CloseUIByString(FString& WidgetClassString);

	UMVCController* GetWidgetController(FGameplayTag WidgetClassTag);

	UPROPERTY(BlueprintReadOnly)
	TMap<FGameplayTag,TObjectPtr<UMVCController>> WidgetControllerMap;
private:

	// UPROPERTY()
	// TObjectPtr<UOverlayController> OverlayWidgetController;
	//
	// UPROPERTY(EditAnywhere)
	// TSubclassOf<UOverlayController> OverlayWidgetControllerClass;

	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag,TSubclassOf<UMVCController>> WidgetControllerClassMap;

	FWidgetControllerParams WidgetControllerParams;
};


