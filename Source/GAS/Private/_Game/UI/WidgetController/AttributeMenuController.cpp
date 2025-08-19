// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/UI/WidgetController/AttributeMenuController.h"

#include "GameplayTagContainer.h"
#include "_Game/GameplayTagsInstance.h"
#include "_Game/Core/AbilitySystem/MyAttributeSet.h"
#include "_Game/Core/AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	const UMyAttributeSet* AS = Cast<UMyAttributeSet>(AttributeSet);
	check(AttributeInfo);

	for (auto& Pair : AS->TagsToAttributes)
	{
		//触发map的委托获取值，然后分发出去
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
}

void UAttributeMenuController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	const UMyAttributeSet* AS = Cast<UMyAttributeSet>(AttributeSet);
	check(AttributeInfo);

	for (auto& Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this,Pair](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Pair.Key, Pair.Value());
			}
		);
	}
}

void UAttributeMenuController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,const FGameplayAttribute& Attribute) const
{
	FGASAttributeInfo Info = AttributeInfo->FindAttributeInfoByTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
	UE_LOG(LogTemp, Display, TEXT("[PeiLog]Broadcast Attribute Info:[%f]"),Info.AttributeValue);
}
