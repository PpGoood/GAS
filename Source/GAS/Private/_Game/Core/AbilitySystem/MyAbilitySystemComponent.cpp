// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Core/AbilitySystem/MyAbilitySystemComponent.h"

#include "_Game/Core/AbilitySystem/Abilities/GASGameplayAbility.h"

void UMyAbilitySystemComponent::InitAbilitySystemComponent()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UMyAbilitySystemComponent::EffectApplied);
}

void UMyAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities)
{
	for (const auto& Ability :  Abilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1);
		if (const UGASGameplayAbility* GASAbility = Cast<UGASGameplayAbility>(AbilitySpec.Ability))
		{
			//添加隐射的tag，可以替换删除，这样能够修改键位
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(GASAbility->DefaultAbilityTag);
			GiveAbility(AbilitySpec);
		}
	}
}

void UMyAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))return;

		//用于触发InputPressed回调，在GA可以实现 激活的第一次不会触发因为会判断IsActive
		AbilitySpecInputPressed(AbilitySpec);
		if (!AbilitySpec.IsActive())
		{
			TryActivateAbility(AbilitySpec.Handle);
		}
	}
}

void UMyAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))return;
		//用于触发InputReleased回调，在GA可以实现
		AbilitySpecInputReleased(AbilitySpec);
	}
}

//GE被应用时候委托调用方法,用于广播标签
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

