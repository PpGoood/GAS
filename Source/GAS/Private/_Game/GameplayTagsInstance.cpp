// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/GameplayTagsInstance.h"

#include "GameplayTagsManager.h"

void GameplayTagsInstance::InitNativeGameplayTags()
{
	
	// 添加所有的 GameplayTag
	// 添加并保存所有的 GameplayTag，同时将它们存储到成员变量
	// 添加并保存所有的 GameplayTag，同时将它们存储到成员变量
	Attributes_Vital_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Health"), FString("必要的生命值"));
	Attributes_Vital_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Mana"), FString("必要的法力值"));

	Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"), FString("力量"));
	Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"), FString("智力"));
	Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resilience"), FString("韧性"));
	Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"), FString("活力"));

	Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("减少受到的伤害"));
	Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"), FString("无视部分护甲"));
	Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"), FString("格挡几率，减少部分伤害"));
	Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitChance"), FString("暴击几率"));
	Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitDamage"), FString("暴击伤害加成"));
	Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitResistance"), FString("暴击抗性，减少受到的暴击伤害"));
	Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"), FString("生命恢复速度"));
	Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"), FString("法力恢复速度"));
	Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"), FString("最大生命值"));
	Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"), FString("最大法力值"));

	Message_HealthCrystal = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.HealthCrystal"), FString("生命水晶提示"));
	Message_HealthPotion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.HealthPotion"), FString("生命药水提示"));
	Message_ManaCrystal = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.ManaCrystal"), FString("法力水晶提示"));
	Message_ManaPotion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.ManaPotion"), FString("法力药水提示"));

	UI_Layer_Game = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.Layer.Game"), FString("游戏层"));
	UI_Layer_Game_OverlayUI = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.Layer.Game.OverlayUI"), FString("游戏层覆盖UI"));
	UI_Layer_GameMenu = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.Layer.GameMenu"), FString("游戏菜单层"));
	UI_Layer_GameMenu_AttributeMenuUI = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.Layer.GameMenu.AttributeMenuUI"), FString("属性菜单UI"));
	UI_Layer_Menu = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.Layer.Menu"), FString("普通菜单层"));
	UI_Layer_Modal = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.Layer.Modal"), FString("模态层"));

	// 输入标签赋值
	InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Action.LMB"), FString("左键"));
	InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Action.RMB"), FString("右键"));
	InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Action.1"), FString("键位1"));
	InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Action.2"), FString("键位2"));
	InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Action.3"), FString("键位3"));
	InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Action.4"), FString("键位4"));

	Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"), FString("伤害"));

	Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitReact"), FString("受到攻击时，赋予的标签"));
}


