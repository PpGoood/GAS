// Fill out your copyright notice in the Description page of Project Settings.

#include "_Game/Core/AbilitySystem/MyAbilitySystemGlobals.h"
#include "_Game/Core/AbilitySystem/CustomAbilityTypes.h"

FGameplayEffectContext* UMyAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FCustomGameplayEffectContext();;
}
