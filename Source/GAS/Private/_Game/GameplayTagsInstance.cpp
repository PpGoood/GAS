// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/GameplayTagsInstance.h"

#include "GameplayTagsManager.h"

void GameplayTagsInstance::InitNativeGameplayTags()
{
	InitInputTags();
	InitUILayoutsTags();
	InitAttributesTags();
	InitDamageTypesTags();
	InitMessageTags();
	InitEffectsTags();
	InitEnvironmentTags();
	InitStateTags();
	InitBuffTags();
	InitAbilityTags();
	InitMontageTags();
}

void GameplayTagsInstance::InitAttributesTags()
{
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

	Attributes_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Fire"), FString("火属性伤害抗性"));
	Attributes_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Lightning"), FString("雷属性抗性"));
	Attributes_Resistance_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Arcane"), FString("魔法攻击抗性"));
	Attributes_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Physical"), FString("物理攻击抗性"));
}

void GameplayTagsInstance::InitDamageTypesTags()
{
	Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Fire"), FString("火焰伤害类型"));
	Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Lightning"), FString("雷属性伤害"));
	Damage_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Arcane"), FString("魔法伤害"));
	Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Physical"), FString("物理伤害"));
	
	DamageTypesToResistances.Add(Damage_Arcane, Attributes_Resistance_Arcane);
	DamageTypesToResistances.Add(Damage_Lightning, Attributes_Resistance_Lightning);
	DamageTypesToResistances.Add(Damage_Physical, Attributes_Resistance_Physical);
	DamageTypesToResistances.Add(Damage_Fire, Attributes_Resistance_Fire);
}

void GameplayTagsInstance::InitUILayoutsTags()
{
	UI_Layer_Game = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.Layer.Game"), FString("游戏层"));
	UI_Layer_Game_OverlayUI = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.Layer.Game.OverlayUI"), FString("游戏层覆盖UI"));
	UI_Layer_GameMenu = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.Layer.GameMenu"), FString("游戏菜单层"));
	UI_Layer_GameMenu_AttributeMenuUI = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.Layer.GameMenu.AttributeMenuUI"), FString("属性菜单UI"));
	UI_Layer_Menu = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.Layer.Menu"), FString("普通菜单层"));
	UI_Layer_Modal = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("UI.Layer.Modal"), FString("模态层"));
}

void GameplayTagsInstance::InitInputTags()
{
	// 输入标签赋值
	InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Action.LMB"), FString("左键"));
	InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Action.RMB"), FString("右键"));
	InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Action.1"), FString("键位1"));
	InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Action.2"), FString("键位2"));
	InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Action.3"), FString("键位3"));
	InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Action.4"), FString("键位4"));
}

void GameplayTagsInstance::InitMessageTags()
{
	Message_HealthCrystal = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.HealthCrystal"), FString("生命水晶提示"));
	Message_HealthPotion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.HealthPotion"), FString("生命药水提示"));
	Message_ManaCrystal = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.ManaCrystal"), FString("法力水晶提示"));
	Message_ManaPotion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.ManaPotion"), FString("法力药水提示"));
}

void GameplayTagsInstance::InitEffectsTags()
{
	Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitReact"), FString("受到攻击时，赋予的标签"));
	Effects_Slow = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.Slow"), FString("减速效果"));
}

void GameplayTagsInstance::InitEnvironmentTags()
{
	Environment_LightObject = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Environment.LightObject"), FString("轻物体"));
	Environment_MediumObject = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Environment.MediumObject"), FString("中等物体"));
}

void GameplayTagsInstance::InitStateTags()
{
	State_ChargingWind = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("State.ChargingWind"), FString("蓄力风"));
	State_GustActive = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("State.GustActive"), FString("技能激活"));
}

void GameplayTagsInstance::InitBuffTags()
{
	Buff_WindMastery = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Buff.WindMastery"), FString("风之精通"));
}

void GameplayTagsInstance::InitAbilityTags()
{
	Cooldown_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Fire.FireBolt"), FString("火球术"));
	Cooldown_Wind_WindCharge = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Wind.WindCharge"), FString("蓄力风技能"));
	Cooldown_Shaman_Summon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Shaman.Summon"), FString("萨满技能"));
	Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Attack"), FString("普通攻击"));
	Abilities_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Fire.FireBolt"), FString("火球攻击"));

}

void GameplayTagsInstance::InitMontageTags()
{
	Montage_Attack_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.Weapon"), FString("使用武器攻击蒙太奇标签"));
	Montage_Attack_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.LeftHand"), FString("使用左手攻击蒙太奇标签"));
	Montage_Attack_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.RightHand"), FString("使用右手攻击蒙太奇标签"));
}






