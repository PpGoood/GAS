// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "WindAbilityDataAsset.generated.h"

struct FGameplayTag;

UENUM(BlueprintType)
enum class EWindChargeType : uint8
{
	Light UMETA(DisplayName = "Light Charge", ToolTip = "轻蓄力阶段"),
	Medium UMETA(DisplayName = "Medium Charge", ToolTip = "中等蓄力阶段"),
	Full UMETA(DisplayName = "Full Charge", ToolTip = "完全蓄力阶段")
};

USTRUCT(BlueprintType)
struct FWindChargeAbilityInfo
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EWindChargeType ChargeType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ChargeTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Range;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DamageScaling;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float WindStrength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UGameplayEffect> CooldownGameplayEffectClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTagContainer ObjectsThatCanBeBlownAwayTags;
	
};
/**
 * 
 */
UCLASS()
class GAS_API UWindAbilityDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	FWindChargeAbilityInfo FindChargeAbilityInfo(EWindChargeType Type);

	FWindChargeAbilityInfo FindChargeAbilityInfoByTime(float ChargeTime);
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FWindChargeAbilityInfo> ChargeAbilityInfos;
};
