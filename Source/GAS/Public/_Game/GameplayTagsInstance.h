#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * GameplayTagsInstance 单例类
 */
class GAS_API GameplayTagsInstance
{
public:
	// 获取单例实例
	static GameplayTagsInstance& GetInstance()
	{
		static GameplayTagsInstance Instance;  // 局部静态变量，首次调用时创建
		return Instance;
	}
	// 禁用拷贝构造和赋值操作符，保证单例唯一性
	GameplayTagsInstance(const GameplayTagsInstance&) = delete;
	GameplayTagsInstance& operator=(const GameplayTagsInstance&) = delete;

	void InitNativeGameplayTags();

	// 所有标签的变量，变量命名以标签名称为准
	FGameplayTag Attributes_Vital_Health;         // Attributes.Vital.Health
	FGameplayTag Attributes_Vital_Mana;           // Attributes.Vital.Mana
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth;  // Attributes.Secondary.MaxHealth
	FGameplayTag Attributes_Secondary_MaxMana;    // Attributes.Secondary.MaxMana
	FGameplayTag Message_HealthCrystal;           // Message.HealthCrystal
	FGameplayTag Message_HealthPotion;            // Message.HealthPotion
	FGameplayTag Message_ManaCrystal;             // Message.ManaCrystal
	FGameplayTag Message_ManaPotion;              // Message.ManaPotion
	FGameplayTag UI_Layer_Game;                   // UI.Layer.Game
	FGameplayTag UI_Layer_Game_OverlayUI;         // UI.Layer.Game.OverlayUI
	FGameplayTag UI_Layer_GameMenu;               // UI.Layer.GameMenu
	FGameplayTag UI_Layer_GameMenu_AttributeMenuUI; // UI.Layer.GameMenu.AttributeMenuUI
	FGameplayTag UI_Layer_Menu;                   // UI.Layer.Menu
	FGameplayTag UI_Layer_Modal;                  // UI.Layer.Modal
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
	FGameplayTag Damage;
	FGameplayTag Effects_HitReact; //受击 标签
private:
	// 私有构造函数和析构函数，防止外部创建实例
	GameplayTagsInstance() = default;
	~GameplayTagsInstance() = default;
};
