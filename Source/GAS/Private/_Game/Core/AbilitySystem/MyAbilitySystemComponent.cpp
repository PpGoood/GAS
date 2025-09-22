// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Core/AbilitySystem/MyAbilitySystemComponent.h"

#include "GAS/GASLogChannels.h"
#include "_Game/Core/AbilitySystem/Abilities/GASGameplayAbility.h"

FGameplayTag UMyAbilitySystemComponent::GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	if(AbilitySpec.Ability)
	{
		for(FGameplayTag Tag : AbilitySpec.Ability.Get()->AbilityTags) //获取设置的所有的技能标签并遍历
		{
			if(Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Abilities")))) //判断当前标签是否包含"Abilities"名称
			{
				return Tag;
			}
		}
	}
	return FGameplayTag();
}

FGameplayTag UMyAbilitySystemComponent::GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	for(FGameplayTag Tag : AbilitySpec.DynamicAbilityTags) //从技能实例的动态标签容器中遍历所有标签
	{
		if(Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Input")))) //查找标签中是否设置以输入标签开头的标签
		{
			return Tag;
		}
	}

	return FGameplayTag();
}

void UMyAbilitySystemComponent::InitAbilitySystemComponent()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UMyAbilitySystemComponent::ClientEffectApplied);
}

void UMyAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities)
{
	for (const auto& Ability :  Abilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1);
		if (const UGASGameplayAbility* GASAbility = Cast<UGASGameplayAbility>(AbilitySpec.Ability))
		{
			//添加隐射的tag，可以替换删除，这样能够修改键位
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(GASAbility->DefaultInputAbilityTag);
			GiveAbility(AbilitySpec);
		}
	}
	bStartupAbilitiesGiven = true;
	AbilityGivenDelegate.Broadcast(this);
}

void UMyAbilitySystemComponent::AddCharacterPassiveAbilities(
	const TArray<TSubclassOf<UGameplayAbility>>& PassiveAbilities)
{
	for(const TSubclassOf<UGameplayAbility> AbilityClass : PassiveAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		GiveAbilityAndActivateOnce(AbilitySpec); //应用技能并激活一次
	}
}

void UMyAbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();
	//为了让客户端也能够成功去广播
	if(!bStartupAbilitiesGiven)
	{
		bStartupAbilitiesGiven = true;
		AbilityGivenDelegate.Broadcast(this);
	}
}


void UMyAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	
	FScopedAbilityListLock ActiveScopeLoc(*this);
	
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UMyAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	FScopedAbilityListLock ActiveScopeLoc(*this);
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag) && AbilitySpec.IsActive())
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

void UMyAbilitySystemComponent::ForEachAbility(const FForEachAbility& Delegate)
{
	FScopedAbilityListLock ActiveScopeLock(*this); //使用域锁将此作用域this的内容锁定（无法修改），在遍历结束时解锁，保证线程安全
	for(const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if(!Delegate.ExecuteIfBound(AbilitySpec)) //运行绑定在技能实例上的委托，如果失败返回false
		{
			UE_LOG(LogGAS, Error, TEXT("在函数[%hs]运行委托失败"), __FUNCTION__);
		}
	}
}


//GE被应用时候委托调用方法,用于广播标签
void UMyAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& GESpec,
	FActiveGameplayEffectHandle GEHandle)
{

	FGameplayTagContainer TagContainer;
	GESpec.GetAllAssetTags(TagContainer);

	EffectAssetTagsDelegate.Broadcast(TagContainer);
	
	// for (const FGameplayTag& Tag : TagContainer)
	// {
	// 	const FString Msg = FString::Printf(TEXT("Tag: %s"), *Tag.ToString());
	// 	GEngine->AddOnScreenDebugMessage(1,1.f,FColor::Blue,Msg);
	// }
	
}

