// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/GASAssetManager.h"

#include "_Game/GameplayTagsInstance.h"

UGASAssetManager& UGASAssetManager::Get()
{
	check(GEngine);

	UGASAssetManager* GASAssetManager = Cast<UGASAssetManager>(GEngine->AssetManager);
	return *GASAssetManager;
}

void UGASAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	GameplayTagsInstance::GetInstance().InitNativeGameplayTags();
}
