// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/UI/WidgetController/OverlayController.h"

#include "_Game/Core/AbilitySystem/MyAbilitySystemComponent.h"
#include "_Game/Core/AbilitySystem/MyAttributeSet.h"

void UOverlayController::BroadcastInitialValues()
{
	const UMyAttributeSet* AttributeSetBase = CastChecked<UMyAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AttributeSetBase->GetHealth());
	OnMaxHealthChanged.Broadcast(AttributeSetBase->GetMaxHealth());
	OnManaChanged.Broadcast(AttributeSetBase->GetMana());
	OnMaxManaChanged.Broadcast(AttributeSetBase->GetMaxMana());

}

void UOverlayController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	const UMyAttributeSet* AttributeSetBase = CastChecked<UMyAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttributeSetBase->GetHealthAttribute()).AddUObject(this, &UOverlayController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	AttributeSetBase->GetMaxHealthAttribute()).AddUObject(this, &UOverlayController::MaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttributeSetBase->GetManaAttribute()).AddUObject(this, &UOverlayController::ManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	AttributeSetBase->GetMaxManaAttribute()).AddUObject(this, &UOverlayController::MaxManaChanged);

	Cast<UMyAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda([](const FGameplayTagContainer& TagContainer)
	{
		for (const FGameplayTag& Tag : TagContainer)
		{
			const FString Msg = FString::Printf(TEXT("Tag: %s"), *Tag.ToString());
			GEngine->AddOnScreenDebugMessage(1,1.f,FColor::Blue,Msg);
		}
	});
}

void UOverlayController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
