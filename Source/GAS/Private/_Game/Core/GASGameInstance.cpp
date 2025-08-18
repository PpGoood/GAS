// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Core/GASGameInstance.h"

#include "_Game/UIManager/UIManagerSubsystem.h"

UCommonActivatableWidget* UGASGameInstance::OpenUI(FGameplayTag WidgetClassTag)
{
	UE_LOG(LogTemp, Display, TEXT("[peiLog]OpenUIByString%s"), *WidgetClassTag.GetTagName().ToString());
	return GetSubsystem<UUIManagerSubsystem>()->OpenUI(WidgetClassTag);
}

void UGASGameInstance::CloseUI(FGameplayTag WidgetClassTag)
{
	UE_LOG(LogTemp, Display, TEXT("[peiLog]OpenUIByString%s"), *WidgetClassTag.GetTagName().ToString());
	GetSubsystem<UUIManagerSubsystem>()->CloseUI(WidgetClassTag);
}

UCommonActivatableWidget* UGASGameInstance::OpenUIByString(FString WidgetClassString)
{
	UE_LOG(LogTemp, Display, TEXT("[peiLog]OpenUIByString%s"), *WidgetClassString);
	return OpenUI(FGameplayTag::RequestGameplayTag(FName(*WidgetClassString)));
}

void UGASGameInstance::CloseUIByString(FString WidgetClassString)
{
	UE_LOG(LogTemp, Display, TEXT("[peiLog]OpenUIByString%s"), *WidgetClassString);
	CloseUI(FGameplayTag::RequestGameplayTag(FName(*WidgetClassString)));
}
