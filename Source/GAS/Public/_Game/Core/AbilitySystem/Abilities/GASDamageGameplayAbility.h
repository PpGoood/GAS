// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "_Game/Core/AbilitySystem/Abilities/GASGameplayAbility.h"
#include "GASDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAS_API UGASDamageGameplayAbility : public UGASGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom|Ability|Damage")
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
	//伤害通过类型以及具体数值添加，这样能够让每个伤害有自己的类型
	UPROPERTY(EditDefaultsOnly, Category="Custom|Ability|Damage")
	TMap<FGameplayTag,FScalableFloat> DamageTypes;
};
