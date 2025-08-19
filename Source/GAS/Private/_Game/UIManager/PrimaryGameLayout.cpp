// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/UIManager/PrimaryGameLayout.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Chaos/Character/CharacterGroundConstraintContainer.h"
#include "Chaos/Deformable/MuscleActivationConstraints.h"
#include "Components/CanvasPanelSlot.h"

void UPrimaryGameLayout::NativeConstruct()
{
	Super::NativeConstruct();
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
		UE_LOG(LogTemp, Warning, TEXT("[PeiLog]PrimaryGameLayout No mapping found for WidgetClass: %s"), *WidgetClassTag.GetTagName().ToString());
		return nullptr;
	}
	
	// 2. 获取映射的层（LayerTag）和 Widget 类（WidgetClassType）
	FGameplayTag LayerTag = WidgetClassTag.RequestDirectParent();
	
	// 3. 推送到对应层
	UCommonActivatableWidget* Widget = PushWidgetToLayerStack(LayerTag, FoundWidgetClass);
	
	if (!Widget)
	{
		UE_LOG(LogTemp, Warning, TEXT("[PeiLog]PrimaryGameLayout Failed to push widget to layer: %s"), *LayerTag.ToString());
		return nullptr;
	}
	
	// 4. 返回 Widget 指针
	UE_LOG(LogTemp, Log, TEXT("[PeiLog]PrimaryGameLayout Successfully opened UI: %s on layer: %s"), *Widget->GetName(), *LayerTag.ToString());
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



