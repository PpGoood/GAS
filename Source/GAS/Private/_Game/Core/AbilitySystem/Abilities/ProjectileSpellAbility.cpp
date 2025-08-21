// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Core/AbilitySystem/Abilities/ProjectileSpellAbility.h"
#include "_Game/Interaction/CombatInterface.h"
#include "_Game/Projectile/ProjectileBase.h"


void UProjectileSpellAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                              const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                              const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UProjectileSpellAbility::SpawnProjectile()
{
	if (!GetAvatarActorFromActorInfo()->HasAuthority())return;
	
	ICombatInterface* CombatInterFace = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	
	if (CombatInterFace == nullptr)return;
	//TODO 设置旋转
	const FVector SocketLocation = CombatInterFace->GetCombatSocketLocation();
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	//需要手动调用生成完成	
	AProjectileBase* Projectile = GetWorld()->SpawnActorDeferred<AProjectileBase>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetAvatarActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);
	//TODO 给ProjectileGE
	Projectile->FinishSpawning(SpawnTransform);	
}