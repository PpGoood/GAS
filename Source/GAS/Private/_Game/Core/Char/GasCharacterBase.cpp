// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Core/Char/GasCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GAS/GAS.h"
#include "_Game/GameplayTagsInstance.h"
#include "_Game/Core/AbilitySystem/MyAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AGasCharacterBase::AGasCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile,ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);
	
	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(FName("WeaponMeshComponent"));
	WeaponMeshComponent->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	WeaponMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAnimMontage* AGasCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

void AGasCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
}

void AGasCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> EffectClass, float Level) const
{
	if (GetAbilitySystemComponent() == nullptr) return;
	if (EffectClass == nullptr) return;
	
	FGameplayEffectContextHandle EffectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(EffectClass,Level,EffectContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}

void AGasCharacterBase::MulticastHandleDeath_Implementation()
{
	//开启武器物理效果
	WeaponMeshComponent->SetSimulatePhysics(true); //开启模拟物理效果
	WeaponMeshComponent->SetEnableGravity(true); //开启重力效果
	WeaponMeshComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly); //开启物理碰撞通道

	//开启角色物理效果
	GetMesh()->SetSimulatePhysics(true); //开启模拟物理效果
	GetMesh()->SetEnableGravity(true); //开启重力效果
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly); //开启物理碰撞通道
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block); //开启角色与静态物体产生碰撞

	//关闭角色碰撞体碰撞通道，避免其对武器和角色模拟物理效果产生影响
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Dissolve();

	bDead = true;
}

void AGasCharacterBase::InitDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes,1);
	ApplyEffectToSelf(DefaultSecondaryAttributes,1);
	ApplyEffectToSelf(DefaultVitalAttributes,1);
}

void AGasCharacterBase::InitDefaultAbilities()
{
	//添加能力只能在服务器进行
	if (!HasAuthority()) return;
	UMyAbilitySystemComponent* ASC = Cast<UMyAbilitySystemComponent>(AbilitySystemComponent);
	ASC->AddCharacterAbilities(StartAbilities);
}

FVector AGasCharacterBase::GetCombatSocketLocation_Implementation()
{
	check(WeaponMeshComponent);
	return WeaponMeshComponent->GetSocketLocation(WeaponTipSocketName);
}

void AGasCharacterBase::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	//添加了受击标签后玩家的受击表现
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
}

void AGasCharacterBase::InitBindEvent()
{
	AbilitySystemComponent->RegisterGameplayTagEvent(GameplayTagsInstance::GetInstance().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ThisClass::HitReactTagChanged);
}

void AGasCharacterBase::Die()
{
	//将武器从角色身上分离
	WeaponMeshComponent->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	MulticastHandleDeath();
}

AActor* AGasCharacterBase::GetAvatar_Implementation()
{
	return this;
}

bool AGasCharacterBase::IsDead_Implementation() const
{
	return bDead;
}

TArray<FTaggedMontage> AGasCharacterBase::GetAttackMontageInfo_Implementation()
{
	return AttackMontageInfo;
}

FVector AGasCharacterBase::GetCombatSocketLocationByInfo_Implementation(const FTaggedMontage TaggedMontage) const
{
	if(TaggedMontage.MontageTag.MatchesTagExact(GameplayTagsInstance::GetInstance().Montage_Attack_Weapon))
	{
		return WeaponMeshComponent->GetSocketLocation(TaggedMontage.CombatTipSocketName);
	}
	else
	{
		return GetMesh()->GetSocketLocation(TaggedMontage.CombatTipSocketName);
	}
}

void AGasCharacterBase::Dissolve()
{
	TArray<UMaterialInstanceDynamic*> MatArray;
	//设置角色溶解
	if(IsValid(DissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);
		GetMesh()->SetMaterial(0, DynamicMatInst);
		MatArray.Add(DynamicMatInst);
	}

	//设置武器溶解
	if(IsValid(WeaponDissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInstance, this);
		WeaponMeshComponent->SetMaterial(0, DynamicMatInst);
		MatArray.Add(DynamicMatInst);
	}

	//调用时间轴渐变溶解
	StartDissolveTimeline(MatArray);
}


