// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MyAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEffectTriggerAssetTags,const FGameplayTagContainer& /**AssetTags**/);

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAbilityChargeChangedSignature,float,float);

DECLARE_MULTICAST_DELEGATE_OneParam(FAbilityGiven, UMyAbilitySystemComponent*) //技能初始化应用后的回调委托

DECLARE_DELEGATE_OneParam(FForEachAbility, const FGameplayAbilitySpec&); //单播委托，只能绑定一个回调

/**
 * 
 */
UCLASS()
class GAS_API UMyAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	static FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	static FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	
	void InitAbilitySystemComponent();

	FOnEffectTriggerAssetTags EffectAssetTagsDelegate;

	FOnAbilityChargeChangedSignature AbilityChargeChangedDelegate;

	FAbilityGiven AbilityGivenDelegate; //技能初始化应用后的回调委托
	//这样子配合委托可以避免用tick或者定时器的写法 无论如何都会被调用
	bool bStartupAbilitiesGiven = false; //初始化应用技能后，此值将被设置为true，用于记录当前是否被初始化完成

	//用于给玩家赋予技能
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities);

	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	void ForEachAbility(const FForEachAbility& Delegate); //遍历技能，并将技能广播出去
protected:
	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& GESpec, FActiveGameplayEffectHandle GEHandle);
};
