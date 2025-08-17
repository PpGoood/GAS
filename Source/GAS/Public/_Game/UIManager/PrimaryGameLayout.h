// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonActivatableWidget.h"
#include "CommonUI/Public/Widgets/CommonActivatableWidgetContainer.h"

#include "CoreMinimal.h"
#include "CommonUIExtensions.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "Engine/StreamableManager.h"
#include "PrimaryGameLayout.generated.h"

//更改为单机单人游戏框架有所改动
/**
 * The state of an async load operation for the UI.
 */
enum class EAsyncWidgetLayerState : uint8
{
	Canceled,
	Initialize,
	AfterPush
};

//需要注册的UI枚举用于快速查找打开UI
// UENUM(BlueprintType)
// enum class EWidgetClass : uint8
// {
// 	Test UMETA(DisplayName = "Test"),
// 	Test2 UMETA(DisplayName = "Test2"),
// };
//改用tag实现

// USTRUCT(BlueprintType)
// struct FWidgetMappingData
// {
// 	GENERATED_BODY()
//
// 	// 枚举：表示UI类别
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "UI.Layer"))
// 	FGameplayTag WidgetClassTag;
//
// 	// 层：UI所在的层
// 	//UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (Categories = "UI.Layer"))
// 	FGameplayTag LayerTag;
//
// 	// 类：对应的Widget类
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 	TSubclassOf<UCommonActivatableWidget> WidgetClassType;
// };

/**
 * 
 */
UCLASS(Abstract, meta = (DisableNativeTick))
class GAS_API UPrimaryGameLayout : public UCommonUserWidget
{
	GENERATED_BODY()
public:
	// //UI管理相关
	// 存储所有的映射关系
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIManager")
	TMap<FGameplayTag,TSubclassOf<UCommonActivatableWidget>> WidgetMappings;	
	// TArray<FWidgetMappingData> WidgetMappings;
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIManager")
	// TArray<FWidgetMappingData> GameLayWidgets;
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIManager")
	// TArray<FWidgetMappingData> GameMenuLayWidgets;
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIManager")
	// TArray<FWidgetMappingData> MenuLayWidgets;
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIManager")
	// TArray<FWidgetMappingData> ModalLayWidgets;

	void NativeConstruct() override;
	
	//休眠
	void SetIsDormant(bool Dormant);
	bool IsDormant() const { return bIsDormant; }
	
	//pushui和removeui
	template <typename ActivatableWidgetT = UCommonActivatableWidget>
	TSharedPtr<FStreamableHandle> PushWidgetToLayerStackAsync(FGameplayTag LayerName, bool bSuspendInputUntilComplete, TSoftClassPtr<UCommonActivatableWidget> ActivatableWidgetClass)
	{
		return PushWidgetToLayerStackAsync<ActivatableWidgetT>(LayerName, bSuspendInputUntilComplete, ActivatableWidgetClass, [](EAsyncWidgetLayerState, ActivatableWidgetT*) {});
	}
	
	template <typename ActivatableWidgetT = UCommonActivatableWidget>
	TSharedPtr<FStreamableHandle> PushWidgetToLayerStackAsync(FGameplayTag LayerName, bool bSuspendInputUntilComplete, TSoftClassPtr<UCommonActivatableWidget> ActivatableWidgetClass, TFunction<void(EAsyncWidgetLayerState, ActivatableWidgetT*)> StateFunc)
	{
		static_assert(TIsDerivedFrom<ActivatableWidgetT, UCommonActivatableWidget>::IsDerived, "Only CommonActivatableWidgets can be used here");

		static FName NAME_PushingWidgetToLayer("PushingWidgetToLayer");

		const FName SuspendInputToken = bSuspendInputUntilComplete ? UCommonUIExtensions::SuspendInputForPlayer(GetOwningPlayer(), NAME_PushingWidgetToLayer) : NAME_None;

		FStreamableManager& StreamableManager = UAssetManager::Get().GetStreamableManager();
		TSharedPtr<FStreamableHandle> StreamingHandle = StreamableManager.RequestAsyncLoad(ActivatableWidgetClass.ToSoftObjectPath(), FStreamableDelegate::CreateWeakLambda(this,
			[this, LayerName, ActivatableWidgetClass, StateFunc, SuspendInputToken]()
			{
				
				UCommonUIExtensions::ResumeInputForPlayer(GetOwningPlayer(), SuspendInputToken);

				ActivatableWidgetT* Widget = PushWidgetToLayerStack<ActivatableWidgetT>(LayerName, ActivatableWidgetClass.Get(), [StateFunc](ActivatableWidgetT& WidgetToInit) {
					StateFunc(EAsyncWidgetLayerState::Initialize, &WidgetToInit);
				});

				StateFunc(EAsyncWidgetLayerState::AfterPush, Widget);
			})
		);

		// Setup a cancel delegate so that we can resume input if this handler is canceled.
		StreamingHandle->BindCancelDelegate(FStreamableDelegate::CreateWeakLambda(this,
			[this, StateFunc,SuspendInputToken]()
			{
				
				UCommonUIExtensions::ResumeInputForPlayer(GetOwningPlayer(), SuspendInputToken);
				StateFunc(EAsyncWidgetLayerState::Canceled, nullptr);
			})
		);

		return StreamingHandle;
	}

	template <typename ActivatableWidgetT = UCommonActivatableWidget>
	ActivatableWidgetT* PushWidgetToLayerStack(FGameplayTag LayerName, UClass* ActivatableWidgetClass)
	{
		return PushWidgetToLayerStack<ActivatableWidgetT>(LayerName, ActivatableWidgetClass, [](ActivatableWidgetT&) {});
	}

	template <typename ActivatableWidgetT = UCommonActivatableWidget>
	ActivatableWidgetT* PushWidgetToLayerStack(FGameplayTag LayerName, UClass* ActivatableWidgetClass, TFunctionRef<void(ActivatableWidgetT&)> InitInstanceFunc)
	{
		static_assert(TIsDerivedFrom<ActivatableWidgetT, UCommonActivatableWidget>::IsDerived, "Only CommonActivatableWidgets can be used here");

		if (UCommonActivatableWidgetContainerBase* Layer = GetLayerWidget(LayerName))
		{
			return Layer->AddWidget<ActivatableWidgetT>(ActivatableWidgetClass, InitInstanceFunc);
		}

		return nullptr;
	}

	// Find the widget if it exists on any of the layers and remove it from the layer.
	void FindAndRemoveWidgetFromLayer(UCommonActivatableWidget* ActivatableWidget);

	// Get the layer widget for the given layer tag.
	UCommonActivatableWidgetContainerBase* GetLayerWidget(FGameplayTag LayerName);

	//方便UI管理器调用
	UCommonActivatableWidget* OpenUI(FGameplayTag WidgetClassTag);
	void CloseUI(UCommonActivatableWidget* ActivatableWidget);
	
protected:
	/** Register a layer that wid
	 * gets can be pushed onto. */
	UFUNCTION(BlueprintCallable, Category="Layer")
	void RegisterLayer(UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag LayerTag, UCommonActivatableWidgetContainerBase* LayerWidget);
	
	virtual void OnIsDormantChanged();

	void OnWidgetStackTransitioning(UCommonActivatableWidgetContainerBase* Widget, bool bIsTransitioning);
	
private:
	bool bIsDormant = false;

	// Lets us keep track of all suspended input tokens so that multiple async UIs can be loading and we correctly suspend
	// for the duration of all of them.
	TArray<FName> SuspendInputTokens;

	// The registered layers for the primary layout.
	UPROPERTY(Transient, meta = (Categories = "UI.Layer"))
	TMap<FGameplayTag, TObjectPtr<UCommonActivatableWidgetContainerBase>> Layers;


	// void InitializeWidgetMappings();
};
