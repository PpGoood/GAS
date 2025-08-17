// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/UIManager/PrimaryGameLayout.h"

#include "Chaos/Character/CharacterGroundConstraintContainer.h"
#include "Chaos/Deformable/MuscleActivationConstraints.h"

void UPrimaryGameLayout::NativeConstruct()
{
	Super::NativeConstruct();
	//InitializeWidgetMappings();
}

void UPrimaryGameLayout::SetIsDormant(bool InDormant)
{
	if (bIsDormant != InDormant)
	{
		const ULocalPlayer* LP = GetOwningLocalPlayer();
		const int32 PlayerId = LP ? LP->GetControllerId() : -1;
		const TCHAR* OldDormancyStr = bIsDormant ? TEXT("Dormant") : TEXT("Not-Dormant");
		const TCHAR* NewDormancyStr = InDormant ? TEXT("Dormant") : TEXT("Not-Dormant");
		const TCHAR* PrimaryPlayerStr = LP && LP->IsPrimaryPlayer() ? TEXT("[Primary]") : TEXT("[Non-Primary]");
		UE_LOG(LogTemp, Display, TEXT("%s PrimaryGameLayout Dormancy changed for [%d] from [%s] to [%s]"), PrimaryPlayerStr, PlayerId, OldDormancyStr, NewDormancyStr);

		bIsDormant = InDormant;
		OnIsDormantChanged();
	}
}

void UPrimaryGameLayout::OnIsDormantChanged()
{
	
}

void UPrimaryGameLayout::FindAndRemoveWidgetFromLayer(UCommonActivatableWidget* ActivatableWidget)
{
	// We're not sure what layer the widget is on so go searching.
	for (const auto& LayerKVP : Layers)
	{
		LayerKVP.Value->RemoveWidget(*ActivatableWidget);
	}
}

UCommonActivatableWidgetContainerBase* UPrimaryGameLayout::GetLayerWidget(FGameplayTag LayerName)
{
	return Layers.FindRef(LayerName);
}

UCommonActivatableWidget* UPrimaryGameLayout::OpenUI(FGameplayTag WidgetClassTag)
{
	// 1. 查找映射关系：根据 WidgetClass 查找对应的层（LayerTag）和 Widget 类
	
	TSubclassOf<UCommonActivatableWidget> FoundWidgetClass = *WidgetMappings.Find(WidgetClassTag);
	if (FoundWidgetClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[peiTest]No mapping found for WidgetClass: %s"), *WidgetClassTag.GetTagName().ToString());
		return nullptr;
	}
	

	// 2. 获取映射的层（LayerTag）和 Widget 类（WidgetClassType）
	FGameplayTag LayerTag = WidgetClassTag.RequestDirectParent();
	// TSubclassOf<UCommonActivatableWidget> WidgetClassType = Data->WidgetClassType;
	//
	// if (!WidgetClassType)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("[peiTest]WidgetClassType is invalid for WidgetClass: %s"), *WidgetClassTag.GetTagName().ToString());
	// 	return nullptr;
	// }

	// 3. 推送到对应层
	UCommonActivatableWidget* Widget = PushWidgetToLayerStack(LayerTag, FoundWidgetClass);
	if (!Widget)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to push widget to layer: %s"), *LayerTag.ToString());
		return nullptr;
	}

	// 4. 返回 Widget 指针
	UE_LOG(LogTemp, Log, TEXT("Successfully opened UI: %s on layer: %s"), *Widget->GetName(), *LayerTag.ToString());
	return Widget;
}


void UPrimaryGameLayout::CloseUI(UCommonActivatableWidget* ActivatableWidget)
{
	FindAndRemoveWidgetFromLayer(ActivatableWidget);
}

void UPrimaryGameLayout::RegisterLayer(FGameplayTag LayerTag, UCommonActivatableWidgetContainerBase* LayerWidget)
{
	if (!IsDesignTime())
	{
		LayerWidget->OnTransitioningChanged.AddUObject(this, &UPrimaryGameLayout::OnWidgetStackTransitioning);
		// TODO: Consider allowing a transition duration, we currently set it to 0, because if it's not 0, the
		//       transition effect will cause focus to not transition properly to the new widgets when using
		//       gamepad always.
		LayerWidget->SetTransitionDuration(0.0);

		Layers.Add(LayerTag, LayerWidget);
	}
}

void UPrimaryGameLayout::OnWidgetStackTransitioning(UCommonActivatableWidgetContainerBase* Widget, bool bIsTransitioning)
{
	if (bIsTransitioning)
	{
		const FName SuspendToken = UCommonUIExtensions::SuspendInputForPlayer(GetOwningLocalPlayer(), TEXT("GlobalStackTransion"));
		SuspendInputTokens.Add(SuspendToken);
	}
	else
	{
		if (ensure(SuspendInputTokens.Num() > 0))
		{
			const FName SuspendToken = SuspendInputTokens.Pop();
			UCommonUIExtensions::ResumeInputForPlayer(GetOwningLocalPlayer(), SuspendToken);
		}
	}
}

// void UPrimaryGameLayout::InitializeWidgetMappings()
// {
// 	// 清空目标数组
// 	WidgetMappings.Empty();
// 	UE_LOG(LogTemp, Log, TEXT("[peiTest] GameLayWidgets contains %d elements."), GameLayWidgets.Num());
// 	UE_LOG(LogTemp, Log, TEXT("[peiTest] GameMenuLayWidgets contains %d elements."), GameMenuLayWidgets.Num());
// 	UE_LOG(LogTemp, Log, TEXT("[peiTest] MenuLayWidgets contains %d elements."), MenuLayWidgets.Num());
// 	UE_LOG(LogTemp, Log, TEXT("[peiTest] ModalLayWidgets contains %d elements."), ModalLayWidgets.Num());
//
// 	// 给每个层的数据添加 LayerTag
// 	for (FWidgetMappingData& Mapping : GameLayWidgets)
// 	{
// 		Mapping.LayerTag = FGameplayTag::RequestGameplayTag(TEXT("UI.Layer.Game"));
// 	}
// 	for (FWidgetMappingData& Mapping : GameMenuLayWidgets)
// 	{
// 		Mapping.LayerTag = FGameplayTag::RequestGameplayTag(TEXT("UI.Layer.GameMenu"));
// 	}
// 	for (FWidgetMappingData& Mapping : MenuLayWidgets)
// 	{
// 		Mapping.LayerTag = FGameplayTag::RequestGameplayTag(TEXT("UI.Layer.Menu"));
// 	}
// 	for (FWidgetMappingData& Mapping : ModalLayWidgets)
// 	{
// 		Mapping.LayerTag = FGameplayTag::RequestGameplayTag(TEXT("UI.Layer.Modal"));
// 	}
//
// 	// 将四个数组合并到 WidgetMappings 中
// 	WidgetMappings.Append(GameLayWidgets);
// 	WidgetMappings.Append(GameMenuLayWidgets);
// 	WidgetMappings.Append(MenuLayWidgets);
// 	WidgetMappings.Append(ModalLayWidgets);
//
// 	// 可选：排序（根据 LayerTag 或其他字段）
// 	WidgetMappings.Sort([](const FWidgetMappingData& A, const FWidgetMappingData& B)
// 	{
// 		// 比如按 LayerTag 排序
// 		return A.LayerTag.ToString() < B.LayerTag.ToString();
// 	});
//
// 	UE_LOG(LogTemp, Log, TEXT("[peiTest]Widget mappings initialized and merged successfully."));
// }

