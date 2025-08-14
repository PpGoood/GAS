// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Core/AbilitySystem/MyAbilitySystemComponent.h"

void UMyAbilitySystemComponent::InitAbilitySystemComponent()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UMyAbilitySystemComponent::EffectApplied);
}

void UMyAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& GESpec,
	FActiveGameplayEffectHandle GEHandle)
{
	GEngine->AddOnScreenDebugMessage(1,1.f,FColor::Blue,"EffectApplied");
}

