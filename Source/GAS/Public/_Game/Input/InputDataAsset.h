// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "InputDataAsset.generated.h"

struct FGameplayTag;
class UInputAction;

USTRUCT(BlueprintType)
struct FGASInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};
/**
 * 
 */
UCLASS()
class GAS_API UInputDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	const UInputAction* FindAbilityInputActionByTag(const FGameplayTag& InputTag,bool bLogNotFound)const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FGASInputAction> AbilityInputActions;
};
