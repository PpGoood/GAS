// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/UIManager/UIManagerSubsystem.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "_Game/UIManager/PrimaryGameLayout.h"

void UUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

bool UUIManagerSubsystem::CreatePrimaryGameLayout()
{
	// 假设 LayoutClass 是 TSoftClassPtr<UPrimaryGameLayout>
	if (LayoutClass.IsNull())
	{
		UE_LOG(LogTemp, Error, TEXT("[peiTest]LayoutClass is null."));
		return false;
	}

	// 同步加载 UPrimaryGameLayout 类
	TSubclassOf<UPrimaryGameLayout> LayoutClassLoaded = LayoutClass.LoadSynchronous();
	
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("[peiTest]Failed find PlayerController"));
		return false;
	}
	
	PrimaryGameLayoutObject = CreateWidget<UPrimaryGameLayout>(PlayerController, LayoutClassLoaded);
	if (PrimaryGameLayoutObject)
	{
		PrimaryGameLayoutObject->AddToViewport();
		UE_LOG(LogTemp, Error, TEXT("[peiTest]Success to load the UPrimaryGameLayout class"));
		return true;
	}

	UE_LOG(LogTemp, Error, TEXT("[peiTest]Failed to load the UPrimaryGameLayout class"));
	return false;
}

UCommonActivatableWidget* UUIManagerSubsystem::OpenUI(FGameplayTag WidgetClassTag)
{
	if (!PrimaryGameLayoutObject)
	{
		UE_LOG(LogTemp, Warning, TEXT("[peiTest]PrimaryGameLayout is null."));
		return nullptr;
	}

	// 推送到对应层
	UCommonActivatableWidget* Widget = PrimaryGameLayoutObject->OpenUI(WidgetClassTag);
	if (!Widget)
	{
		UE_LOG(LogTemp, Warning, TEXT("[peiTest]Failed to push widget to layer."));
		return nullptr;
	}

	// 存入激活列表（如有旧值，替换）
	ActiveUIWidgets.FindOrAdd(WidgetClassTag) = Widget;

	// 使用枚举的值输出日志
	UE_LOG(LogTemp, Log, TEXT("[peiTest]Opened UI: %s"), *WidgetClassTag.GetTagName().ToString());
	return Widget;
}

void UUIManagerSubsystem::CloseUI(FGameplayTag WidgetClassTag)
{
	if (!PrimaryGameLayoutObject)
	{
		UE_LOG(LogTemp, Warning, TEXT("PrimaryGameLayoutObject is null."));
		return;
	}

	// 查找当前激活的 Widget
	UCommonActivatableWidget* FoundWidget = ActiveUIWidgets.FindRef(WidgetClassTag);
	if (!FoundWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("No active widget found for WidgetClass: %s."), *WidgetClassTag.GetTagName().ToString());
		return;
	}

	// 如果 FoundWidget 非空，则移除 UI
	if (PrimaryGameLayoutObject)
	{
		PrimaryGameLayoutObject->CloseUI(FoundWidget);
		UE_LOG(LogTemp, Log, TEXT("Closed UI: %s"), *FoundWidget->GetName());
	}

	// 从激活列表中移除
	ActiveUIWidgets.Remove(WidgetClassTag);

	// 确保从 UI 列表中移除并记录
	UE_LOG(LogTemp, Log, TEXT("Successfully removed WidgetClass: %s from Active UI list."), *WidgetClassTag.GetTagName().ToString());
}

void UUIManagerSubsystem::DelayFun()
{
	
}





