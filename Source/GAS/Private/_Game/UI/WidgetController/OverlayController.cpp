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

	//GetGameplayAttributeValueChangeDelegate 为获取属性改变委托的方法，绑定新的委托触发
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttributeSetBase->GetHealthAttribute()).AddLambda( [this](const FOnAttributeChangeData& Data){
		OnHealthChanged.Broadcast(Data.NewValue); 
		});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttributeSetBase->GetMaxHealthAttribute()).AddLambda( [this](const FOnAttributeChangeData& Data){
			OnMaxHealthChanged.Broadcast(Data.NewValue);  
		});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttributeSetBase->GetManaAttribute()).AddLambda( [this](const FOnAttributeChangeData& Data){
			OnManaChanged.Broadcast(Data.NewValue);  
		});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttributeSetBase->GetMaxManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data){
			OnMaxManaChanged.Broadcast(Data.NewValue); 
		});

	UMyAbilitySystemComponent* GASASC = Cast<UMyAbilitySystemComponent>(AbilitySystemComponent);
	if (GASASC == nullptr) return;

	if (GASASC->bStartupAbilitiesGiven)
	{
		OnInitializeStartupAbilities(GASASC);
	}
	else
	{
		GASASC->AbilityGivenDelegate.AddUObject(this, &ThisClass::OnInitializeStartupAbilities);
	}
	
	GASASC->EffectAssetTagsDelegate.AddLambda([this](const FGameplayTagContainer& TagContainer)
	{
		for (const FGameplayTag& Tag : TagContainer)
		{
			FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
			if (Tag.MatchesTag(MessageTag))
			{
				const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable,Tag);
				MessageWidgetRowDelegate.Broadcast(*Row);
			}
		}
	});

	GASASC->AbilityChargeChangedDelegate.AddLambda([this](float ChargeTime,float MaxChargeTime)
	{
		ChargeChangedDelegate.Broadcast(ChargeTime,MaxChargeTime);
	});
	
}

void UOverlayController::OnInitializeStartupAbilities(UMyAbilitySystemComponent* ASC) const
{
	if(!ASC->bStartupAbilitiesGiven) return; //判断当前技能初始化是否完成，触发回调时都已经完成

	FForEachAbility BroadcastDelegate;
	//委托绑定回调匿名函数，委托广播时将会触发函数内部逻辑
	BroadcastDelegate.BindLambda([this](const FGameplayAbilitySpec& AbilitySpec)
	{
		//通过静态函数获取到技能实例的技能标签，并通过标签获取到技能数据
		FGASAbilityIconInfo Info = AbilityIconInfo->FindAbilityInfoForTag(UMyAbilitySystemComponent::GetAbilityTagFromSpec(AbilitySpec));
		//获取到技能的输入标签
		Info.InputTag = UMyAbilitySystemComponent::GetInputTagFromSpec(AbilitySpec);
		AbilityInfoDelegate.Broadcast(Info); 
	});
	//遍历技能并触发委托回调
	ASC->ForEachAbility(BroadcastDelegate);
}


