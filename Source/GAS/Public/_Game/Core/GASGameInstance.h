// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GASGameInstance.generated.h"

//TODO用其他的方法调用子系统
class UCommonActivatableWidget;
struct FGameplayTag;
/**
 * 
 */
UCLASS()
class GAS_API UGASGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	UCommonActivatableWidget* OpenUI(FGameplayTag WidgetClassTag);
	UFUNCTION(BlueprintCallable)
	void CloseUI(FGameplayTag WidgetClassTag);

	UFUNCTION(BlueprintCallable)
	UCommonActivatableWidget* OpenUIByString(FString WidgetClassString);
	UFUNCTION(BlueprintCallable)
	void CloseUIByString(FString WidgetClassString);
};
