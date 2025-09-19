// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "_Game/Core/AbilitySystem/MyAbilitySystemComponent.h"
#include "_Game/Core/AbilitySystem/MyAttributeSet.h"
#include "_Game/Data/AbilityIconInfo.h"
#include "_Game/UI/Widget/MVCWidget.h"
#include "_Game/UI/WidgetController/MVCController.h"
#include "OverlayController.generated.h"

class UAbilityIconInfo;

USTRUCT(BlueprintType)
struct FUIWidgetRow:public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UMVCWidget> MessageWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature,float, NewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature,FUIWidgetRow,Row);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUIChargeChangedSignature,float,CurCharge,float,MaxCharge);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityInfoSignature, const FGASAbilityIconInfo, Info);
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class GAS_API UOverlayController : public UMVCController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category="Custom|GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="Custom|GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="Custom|GAS|Attributes")
	FOnAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category="Custom|GAS|Attributes")
	FOnAttributeChangedSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category="Custom|Message")
	FMessageWidgetRowSignature MessageWidgetRowDelegate;

	UPROPERTY(BlueprintAssignable, Category="Custom|Messages")
	FAbilityInfoSignature AbilityInfoDelegate;
	
	UPROPERTY(BlueprintAssignable, Category="Custom|Message")
	FOnUIChargeChangedSignature ChargeChangedDelegate;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="Custom|Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;

	//使用tag去查找datatable的数据，需要datatable每行的名称与Tag的名称完全一致
	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable,const FGameplayTag& Tag);
	
	//技能的表格数据
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Custom|Widget Data")
	TObjectPtr<UAbilityIconInfo> AbilityIconInfo;

	void OnInitializeStartupAbilities(UMyAbilitySystemComponent* ASC) const; //技能初始化应用后的回调
};

template <typename T>
T* UOverlayController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	T* RowData = DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
	return RowData == nullptr ? nullptr : RowData;
}
