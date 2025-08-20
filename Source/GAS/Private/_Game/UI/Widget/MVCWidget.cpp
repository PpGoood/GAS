// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/UI/Widget/MVCWidget.h"

#include "Kismet/GameplayStatics.h"
#include "_Game/UI/HUD/MVCHUD.h"

void UMVCWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet_Event();

}

//此方法依赖于MVCHUD
void UMVCWidget::SetWidgetControllerByHUD(FGameplayTag WidgetTag)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[PeiLog]UMVCWidget PlayerController is null"));
		return;
	}
	AMVCHUD* HUD = Cast<AMVCHUD>(PlayerController->GetHUD());
	if (HUD == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[PeiLog]UMVCWidget HUD is null"));
		return;
	}

	UMVCController* UmvcController = *HUD->WidgetControllerMap.Find(WidgetTag);
	if (UmvcController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[PeiLog]UMVCWidget WidgetController is null"));
		return;
	}

	SetWidgetController(UmvcController);
}
