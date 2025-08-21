// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/UI/HUD/MVCHUD.h"

#include "_Game/GameplayTagsInstance.h"
#include "_Game/UI/WidgetController/MVCController.h"
#include "_Game/UI/WidgetController/OverlayController.h"
#include "_Game/UIManager/UIManagerSubsystem.h"

// UOverlayController* AMVCHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
// {
// 	if(OverlayWidgetController == nullptr)
// 	{
// 		OverlayWidgetController = NewObject<UOverlayController>(this, OverlayWidgetControllerClass);
// 		OverlayWidgetController->SetWidgetControllerParmas(WCParams);
// 	}
// 	return OverlayWidgetController;
// }

UMVCController* AMVCHUD::GetWidgetController(FGameplayTag WidgetClassTag)
{
	UMVCController* WidgetController = nullptr;

	if(WidgetControllerMap.Find(WidgetClassTag))
	{
		return WidgetController;
	}
	//创建对应的Conroller
	if (WidgetControllerClassMap.Find(WidgetClassTag) == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[PeiLog]Widget Controller Class not Found"));
		return nullptr;
	}
	if (TSubclassOf<UMVCController> ControllerClass = WidgetControllerClassMap.Find(WidgetClassTag)->Get())
	{
		WidgetController = NewObject<UMVCController>(this, ControllerClass);
		WidgetController->SetWidgetControllerParmas(WidgetControllerParams);
	}
	return WidgetController;
}

void AMVCHUD::InitControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	
	//checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass 未设置，请在HUD上面设置"));
	WidgetControllerParams =  FWidgetControllerParams(PC, PS, ASC, AS); //创建参数结构体

	//创建界面UI
	UUIManagerSubsystem* UIManager = GetGameInstance()->GetSubsystem<UUIManagerSubsystem>();
	UIManager->CreatePrimaryGameLayout();
	OpenUI(GameplayTagsInstance::GetInstance().UI_Layer_Game_OverlayUI);
}

UCommonActivatableWidget* AMVCHUD::OpenUI(FGameplayTag WidgetClassTag)
{
	//打开UI的时候会动态生成Controller并设置
	UE_LOG(LogTemp, Display, TEXT("[PeiLog]OpenUIByString%s"), *WidgetClassTag.GetTagName().ToString());
	UCommonActivatableWidget* CommonUI = GetGameInstance()->GetSubsystem<UUIManagerSubsystem>()->OpenUI(WidgetClassTag);
	UMVCWidget* MVCUI = Cast<UMVCWidget>(CommonUI);
	if (WidgetControllerMap.Find(WidgetClassTag) == nullptr)
	{
		//第一次创建绑定需要初始化
		UMVCController* WidgetController = GetWidgetController(WidgetClassTag);
		//设置了之后会触发WidgetControllerSet_Event方法
		MVCUI->SetWidgetController(WidgetController);
		WidgetController->BroadcastInitialValues(); //初始化广播
		WidgetController->BindCallbacksToDependencies(); //绑定监听数值变化
		WidgetControllerMap.Add(WidgetClassTag, WidgetController);
	}
	return CommonUI;
}

void AMVCHUD::CloseUI(FGameplayTag WidgetClassTag)
{
	UE_LOG(LogTemp, Display, TEXT("[PeiLog]OpenUIByString%s"), *WidgetClassTag.GetTagName().ToString());
	GetGameInstance()->GetSubsystem<UUIManagerSubsystem>()->CloseUI(WidgetClassTag);
}

UCommonActivatableWidget* AMVCHUD::OpenUIByString(FString& WidgetClassString)
{
	return OpenUI(FGameplayTag::RequestGameplayTag(FName(WidgetClassString)));
}

void AMVCHUD::CloseUIByString(FString& WidgetClassString)
{
	CloseUI(FGameplayTag::RequestGameplayTag(FName(WidgetClassString)));
}
