// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GASGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAS_API UGASGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category="Custom|Ability|Input")
	FGameplayTag DefaultInputAbilityTag;

	UPROPERTY(EditDefaultsOnly, Category="Custom|Ability|Damage")
	FScalableFloat Damage;
};
