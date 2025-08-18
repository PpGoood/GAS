// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/UI/HUD/MVCHUD.h"

#include "_Game/UI/WidgetController/MVCController.h"
#include "_Game/UI/WidgetController/OverlayController.h"
#include "_Game/UIManager/UIManagerSubsystem.h"

UOverlayController* AMVCHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if(OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParmas(WCParams);
	}
	return OverlayWidgetController;
}

void AMVCHUD::InitPrimary(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass 未设置，请在HUD上面设置"));
	
	
	UUIManagerSubsystem* UIManager = GetGameInstance()->GetSubsystem<UUIManagerSubsystem>();
	UIManager->CreatePrimaryGameLayout();

	UMVCWidget* MainUI = Cast<UMVCWidget>(UIManager->OpenUI(FGameplayTag::RequestGameplayTag(FName("UI.Layer.Game.OverlayUI"))));
	
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS); //创建参数结构体
	OverlayWidgetController = GetOverlayWidgetController(WidgetControllerParams); //获取控制器层
	MainUI->SetWidgetController(OverlayWidgetController);
	
	OverlayWidgetController->BroadcastInitialValues(); //初始化广播
	OverlayWidgetController->BindCallbacksToDependencies(); //绑定监听数值变化
	
}
