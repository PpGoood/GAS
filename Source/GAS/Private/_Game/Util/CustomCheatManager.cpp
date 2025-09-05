// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Util/CustomCheatManager.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilities/Private/AbilitySystemCheatManagerExtension.h"
#include "Engine/Engine.h"  // 引入 GEngine 用于显示日志
#include "_Game/GameplayTagsInstance.h"
#include "_Game/Core/AbilitySystem/Abilities/WindChargeAbility.h"
#include "_Game/Core/Char/GasCharacterBase.h"

class AWindDamageArea;
class UGameplayEffect;

void UCustomCheatManager::AddWindMastery()
{
    // 获取玩家控制器并检查是否有效
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    // 获取玩家的 Ability System Component
    UAbilitySystemComponent* ASC = Cast<AGasCharacterBase>(PC->GetPawn())->GetAbilitySystemComponent();
    // 加载蓝图资源并获取其生成的类
    FString GEPath = TEXT("/Game/_Game/Blueprints/GAS/GE/Buff/GE_WindMastery.GE_WindMastery"); // 确保路径正确
    UBlueprint* Blueprint = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), nullptr, *GEPath));
	
    // 获取蓝图生成的类（注意：它必须是一个GameplayEffect类）
    UClass* GeneratedClass = Blueprint->GeneratedClass;
    // 获取GameplayEffect的默认对象实例
    UGameplayEffect* GameplayEffect = Cast<UGameplayEffect>(GeneratedClass->GetDefaultObject());
    // 创建 GameplayEffectSpec
    FGameplayEffectContextHandle GEContext = ASC->MakeEffectContext();
    APawn* Pawn = PC->GetPawn();
    GEContext.AddInstigator(Pawn, Pawn);
    GEContext.AddOrigin(Pawn->GetActorLocation());
	
    FGameplayEffectSpec GESpec(GameplayEffect, GEContext);
	
    FPredictionKey FakePredictionKey = FPredictionKey::CreateNewPredictionKey(ASC);
    ASC->ApplyGameplayEffectSpecToSelf(GESpec, FakePredictionKey);

    UE_LOG(LogTemp, Log, TEXT("Successfully applied GameplayEffect '%s' to Player '%s'."), *GameplayEffect->GetName(), *PC->GetName());
}


void UCustomCheatManager::ForceGust(int Level)
{
	// 获取玩家控制器并检查是否有效
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	// 获取玩家的 Ability System Component
	UAbilitySystemComponent* ASC = Cast<AGasCharacterBase>(PC->GetPawn())->GetAbilitySystemComponent();

	for (FGameplayAbilitySpec& AbilitySpec : ASC->GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(GameplayTagsInstance::GetInstance().InputTag_1))
		{
			if (!AbilitySpec.IsActive())
			{
				ASC->TryActivateAbility(AbilitySpec.Handle);
				if (UGASChargeAbility* ChargeAbility = Cast<UGASChargeAbility>(AbilitySpec.Ability))
				{
					ChargeAbility->bIsCharging = true;
					switch (Level)
					{
						case 1:
							ChargeAbility->CurrentChargeTime = 0;
							break;
						case 2:
							ChargeAbility->CurrentChargeTime = 1;
							break;
						case 3:
							ChargeAbility->CurrentChargeTime = 1.5;
							break;
						default:
							ChargeAbility->CurrentChargeTime = 0;
							break;
					}
				}
				ASC->AbilitySpecInputReleased(AbilitySpec);
			}
		}
	}
}

void UCustomCheatManager::ResetRingCooldown()
{
	// 获取玩家控制器并检查是否有效
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	// 获取玩家的 Ability System Component
	UAbilitySystemComponent* ASC = Cast<AGasCharacterBase>(PC->GetPawn())->GetAbilitySystemComponent();
	// 获取 Cooldown_Wind_WindCharge 标签
	FGameplayTag CooldownTag = GameplayTagsInstance::GetInstance().Cooldown_Wind_WindCharge;
	// 移除标签
	ASC->RemoveLooseGameplayTag(CooldownTag);
}


