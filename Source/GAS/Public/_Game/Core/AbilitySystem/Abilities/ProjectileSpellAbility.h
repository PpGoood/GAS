// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "_Game/Core/AbilitySystem/Abilities/GASGameplayAbility.h"
#include "ProjectileSpellAbility.generated.h"

class AProjectileBase;
/**
 * 
 */
UCLASS()
class GAS_API UProjectileSpellAbility : public UGASGameplayAbility
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom|Ability")
	TSubclassOf<AProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom|Ability")
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category = "Custom|Ability")
	void SpawnProjectile(const FVector& ProjectileTargetLocation);

};
