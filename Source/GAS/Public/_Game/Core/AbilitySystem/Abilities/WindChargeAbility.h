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
	UPROPERTY(EditDefaultsOnly, Category = "Custom|Charge Ability")
	TObjectPtr<UWindAbilityDataAsset> WindAbilityDataAsset;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom|Ability")
	TSubclassOf<AWindDamageArea> DamageAreaClass;
	virtual void ActivateChargeAbility() override;

	UFUNCTION(BlueprintCallable, Category = "Custom|Ability")
	void SpawnDamageArea();
	
};
