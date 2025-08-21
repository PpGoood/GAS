// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlueprintGameplayTagLibrary.h"
#include "BlueprintGameplayTagLibraryUtil.generated.h"

/**
 * 
 */
UCLASS()
class GAS_API UBlueprintGameplayTagLibraryUtil : public UBlueprintGameplayTagLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Gameplay Tags")
	static FGameplayTag GetTagFromString(const FString& TagString)
	{
		FName TagName(*TagString); // 将 FString 转换为 FName
		return FGameplayTag::RequestGameplayTag(TagName);
	}
};
