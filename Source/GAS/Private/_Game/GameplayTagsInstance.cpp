// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/GameplayTagsInstance.h"

#include "GameplayTagsManager.h"

void GameplayTagsInstance::InitNativeGameplayTags()
{
	
	// 添加所有的 GameplayTag
	// 添加并保存所有的 GameplayTag，同时将它们存储到成员变量
	Attributes_Vital_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Health"), FString("必要的生命值"));
	Attributes_Vital_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Mana"), FString("必要的法力值"));
	Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"), FString("力量"));
	Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"), FString("智力"));
	Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resilience"), FString("韧性"));
	Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"), FString("活力"));
	Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Reduces damage taken"));
	Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"), FString("Ignores armor"));
	Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"), FString("Chance to cut incoming damage"));
	Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitChance"), FString("Chance to do critical damage"));
	Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitDamage"), FString("Bonus damage on critical hits"));
	Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitResistance"), FString("Reduces critical damage received"));
	Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"), FString("Amount of health regenerated"));
	Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"), FString("Amount of mana regenerated"));
	Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"), FString("最大生命值"));
	Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"), FString("最大法力值"));

	Message_HealthCrystal = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.HealthCrystal"), FString(""));
	Message_HealthPotion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.HealthPotion"), FString(""));
	Message_ManaCrystal = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.ManaCrystal"), FString(""));
	Message_ManaPotion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.ManaPotion"), FString(""));

	UI_Layer_Game = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.Layer.Game"), FString(""));
	UI_Layer_Game_OverlayUI = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.Layer.Game.OverlayUI"), FString(""));
	UI_Layer_GameMenu = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.Layer.GameMenu"), FString(""));
	UI_Layer_GameMenu_AttributeMenuUI = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.Layer.GameMenu.AttributeMenuUI"), FString(""));
	UI_Layer_Menu = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.Layer.Menu"), FString(""));
	UI_Layer_Modal = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.Layer.Modal"), FString(""));
}


