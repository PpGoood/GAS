// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "_Game/Core/AbilitySystem/Abilities/GASChargeAbility.h"
#include "WindChargeAbility.generated.h"

class AWindDamageArea;
/**
 * 
 */
UCLASS()
class GAS_API UWindChargeAbility : public UGASChargeAbility
{
	GENERATED_BODY()
public:
	const float BUFF_EXTRA_BONUS = 1.4f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Custom|Wind Ability")
	TObjectPtr<UWindAbilityDataAsset> WindAbilityDataAsset;

	UFUNCTION(BlueprintCallable, Category = "Custom|Wind Ability")
	void SpawnDamageArea();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom|Wind Ability")
	TSubclassOf<AWindDamageArea> DamageAreaClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom|Wind Ability|Damage")
	TSubclassOf<UGameplayEffect> DebuffEffectClass;
	
	virtual void ActivateChargeAbility() override;

	virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;

	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
private:
	FWindChargeAbilityInfo CurrentChargeAbilityInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Custom|Wind Ability")
	TSubclassOf<AActor> SkillRangeCircleClass;

	TObjectPtr<AActor> SkillRangeCircle;
};
