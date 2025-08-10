// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/UI/WidgetController/OverlayController.h"

#include "_Game/Core/AbilitySystem/MyAttributeSet.h"

void UOverlayController::BroadcastInitialValues()
{
	const UMyAttributeSet* AttributeSetBase = CastChecked<UMyAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AttributeSetBase->GetHealth());
	OnMaxHealthChanged.Broadcast(AttributeSetBase->GetMaxHealth());

}

void UOverlayController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	const UMyAttributeSet* AttributeSetBase = CastChecked<UMyAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttributeSetBase->GetHealthAttribute()).AddUObject(this, &UOverlayController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	AttributeSetBase->GetMaxHealthAttribute()).AddUObject(this, &UOverlayController::MaxHealthChanged);
	
}

void UOverlayController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}
