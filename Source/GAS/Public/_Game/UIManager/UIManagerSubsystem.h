// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "PrimaryGameLayout.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UIManagerSubsystem.generated.h"

//此版本为测试版本只考虑单人游戏的单人屏幕
class UCommonActivatableWidget;

/**
 * 
 */
UCLASS(config = Game)
class GAS_API UUIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	//void InitPrimaryGameLayout();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override{return !CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance();}
	
	//UI管理相关
	TMap<FGameplayTag, UCommonActivatableWidget*> ActiveUIWidgets; // 记录不同层的UI控件

	bool CreatePrimaryGameLayout();
	
	UCommonActivatableWidget* OpenUI(FGameplayTag WidgetClassTag);
	void CloseUI(FGameplayTag WidgetClassTag);
	

private:
	UPROPERTY(Config,EditAnywhere)
	TSoftClassPtr<UPrimaryGameLayout> LayoutClass;
	
	TObjectPtr<UPrimaryGameLayout> PrimaryGameLayoutObject;
	FTimerHandle TimerHandle; // 计时器句柄
	
	void DelayFun();
};
