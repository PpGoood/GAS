// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Core/AbilitySystem/Abilities/WindChargeAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "_Game/WindDamageArea.h"
#include "AbilitySystemComponent.h"
#include "_Game/GameplayTagsInstance.h"

void UWindChargeAbility::ActivateChargeAbility()
{
	Super::ActivateChargeAbility();
	SpawnDamageArea();
}

void UWindChargeAbility::SpawnDamageArea()
{
	check(DamageAreaClass);
	//在自身范围内生成
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer)return;
	
	APawn* Pawn = Cast<APawn>(GetAvatarActorFromActorInfo());
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(Pawn->GetActorLocation());
	SpawnTransform.SetRotation(FRotator::ZeroRotator.Quaternion());

	AWindDamageArea* DamageArea = GetWorld()->SpawnActorDeferred<AWindDamageArea>(
		DamageAreaClass,
		SpawnTransform,
		Pawn,
		Pawn,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);
	const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	
	FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
	EffectContextHandle.SetAbility(this);
	EffectContextHandle.AddSourceObject(DamageArea);

	const FGameplayEffectSpecHandle DamegeSpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass,GetAbilityLevel(),SourceASC->MakeEffectContext());

	if (SourceASC->HasMatchingGameplayTag(GameplayTagsInstance::GetInstance().Buff_WindMastery))
	{
		FGameplayEffectSpecHandle DebuffSpecHandle = SourceASC->MakeOutgoingSpec(DebuffEffectClass,GetAbilityLevel(),SourceASC->MakeEffectContext());
		DamageArea->DebuffEffectSpecHandle = DebuffSpecHandle;
	}
	else
	{
		DamageArea->DebuffEffectSpecHandle = nullptr;
	}
	
	for (auto& Pair:DamageTypes)
	{
		//TODOScaledDamage需要根据buff进行加成
		const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamegeSpecHandle,Pair.Key,ScaledDamage);
	}

	DamageArea->DamageEffectSpecHandle = DamegeSpecHandle;
	DamageArea->WindChargeAbilityInfo = WindAbilityDataAsset->FindChargeAbilityInfoByTime(CurrentChargeTime);
	DamageArea->FinishSpawning(SpawnTransform);	
}


