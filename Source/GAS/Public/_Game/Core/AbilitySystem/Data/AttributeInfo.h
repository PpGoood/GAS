// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"

struct FGameplayTag;

USTRUCT(BlueprintType)
struct FGASAttributeInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();
	
	//FText可以用于本地化
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeDescription = FText();

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.0f;
};

/**
 * 
 */
UCLASS()
class GAS_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	FGASAttributeInfo FindAttributeInfoByTag(const FGameplayTag AttributeTag,bool bLogNotFound = false)const;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FGASAttributeInfo> AttributeInformations;
};
