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

void UProjectileSpellAbility::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	if (!GetAvatarActorFromActorInfo()->HasAuthority())return;
	
	ICombatInterface* CombatInterFace = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	
	if (CombatInterFace == nullptr)return;
	
	const FVector SocketLocation = CombatInterFace->GetCombatSocketLocation();
	FRotator SpawnRotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	SpawnRotation.Pitch = 0.f;
	
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(SpawnRotation.Quaternion());
	
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