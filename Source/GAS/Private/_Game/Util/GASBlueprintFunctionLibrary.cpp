// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Util/GASBlueprintFunctionLibrary.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "Kismet/GameplayStatics.h"
#include "_Game/Core/TopDownGameMode.h"
#include "_Game/Core/AbilitySystem/Data/CharacterClassInfo.h"


void UGASBlueprintFunctionLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject,
                                                               ECharacterClassType CharacterClass, float Level,UAbilitySystemComponent* ASC)
{
	UCharacterClassInfo* ClassInfo = GetCharacterClassInfo(WorldContextObject);
	FCharacterClassDefaultInfo ClassDefaultInfo = ClassInfo->GetClassDefaultInfo(CharacterClass);

	//应用基础属性
	FGameplayEffectContextHandle PrimaryContextHandle = ASC->MakeEffectContext();
	PrimaryContextHandle.AddSourceObject(WorldContextObject);
	const FGameplayEffectSpecHandle PrimarySpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimarySpecHandle.Data.Get());

	//设置次级属性
	FGameplayEffectContextHandle SecondaryContextHandle = ASC->MakeEffectContext();
	SecondaryContextHandle.AddSourceObject(WorldContextObject);
	const FGameplayEffectSpecHandle SecondarySpecHandle = ASC->MakeOutgoingSpec(ClassInfo->SecondaryAttributes, Level, SecondaryContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondarySpecHandle.Data.Get());

	//填充血量和蓝量
	FGameplayEffectContextHandle VitalContextHandle = ASC->MakeEffectContext();
	VitalContextHandle.AddSourceObject(WorldContextObject);
	const FGameplayEffectSpecHandle VitalSpecHandle = ASC->MakeOutgoingSpec(ClassInfo->VitalAttributes, Level, VitalContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalSpecHandle.Data.Get());
}

void UGASBlueprintFunctionLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC)
{
	// //获取到当前关卡的GameMode实例
	// ATopDownGameMode* GameMode = Cast<ATopDownGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	// if (GameMode == nullptr) return;

	const AActor* AvatarActor = ASC->GetAvatarActor();
	if (!AvatarActor->HasAuthority()) return;
	//从实例获取到关卡角色的配置
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);

	//遍历角色拥有的技能数组
	for(const TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1); //创建技能实例
		ASC->GiveAbility(AbilitySpec); //只应用不激活
	}
}

UCharacterClassInfo* UGASBlueprintFunctionLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	ATopDownGameMode* GameMode = Cast<ATopDownGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (GameMode == nullptr) return nullptr;

	return GameMode->CharacterClassInfo;
}

