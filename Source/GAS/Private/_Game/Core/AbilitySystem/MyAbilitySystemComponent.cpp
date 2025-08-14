// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Core/AbilitySystem/MyAbilitySystemComponent.h"

void UMyAbilitySystemComponent::InitAbilitySystemComponent()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UMyAbilitySystemComponent::EffectApplied);
}

void UMyAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& GESpec,
	FActiveGameplayEffectHandle GEHandle)
{

	FGameplayTagContainer TagContainer;
	GESpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
	
	// for (const FGameplayTag& Tag : TagContainer)
	// {
	// 	const FString Msg = FString::Printf(TEXT("Tag: %s"), *Tag.ToString());
	// 	GEngine->AddOnScreenDebugMessage(1,1.f,FColor::Blue,Msg);
	// }
	
}

