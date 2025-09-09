// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfo.generated.h"

class UGameplayAbility;
class UGameplayEffect;

UENUM(BlueprintType)
enum class ECharacterClassType : uint8
{
	Elementalist UMETA(DisplayName = "Elementalist", ToolTip = "法师"),
	Warrior UMETA(DisplayName = "Warrior", ToolTip = "战士"),
	Ranger UMETA(DisplayName = "Ranger", ToolTip = "游侠")
};

USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,Category="Class Defaults")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;

	UPROPERTY(EditDefaultsOnly,Category="Class Defaults")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};
/**
 * 
 */
UCLASS()
class GAS_API UCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:
	//通过职业去更换不同的主要属性从而影响其他的属性
	UPROPERTY(EditDefaultsOnly, Category="Class Defaults")
	TMap<ECharacterClassType, FCharacterClassDefaultInfo> CharacterClassInformation;
	
	UPROPERTY(EditDefaultsOnly, Category="Common Class Defaults")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;
	
	UPROPERTY(EditDefaultsOnly, Category="Common Class Defaults")
	TSubclassOf<UGameplayEffect> VitalAttributes;

	UPROPERTY(EditDefaultsOnly, Category="Common Class Defaults")
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;

	UPROPERTY(EditDefaultsOnly, Category="Common Class Defaults")
	TObjectPtr<UCurveTable> DamageCalculationTable;

	//通过枚举获取对应的初始化类
	FCharacterClassDefaultInfo GetClassDefaultInfo(ECharacterClassType CharacterClass);

};
