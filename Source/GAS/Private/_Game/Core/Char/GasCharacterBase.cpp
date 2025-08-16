// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Core/Char/GasCharacterBase.h"
#include "AbilitySystemComponent.h"

// Sets default values
AGasCharacterBase::AGasCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(FName("WeaponMeshComponent"));
	WeaponMeshComponent->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	WeaponMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AGasCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AGasCharacterBase::InitializePrimaryAttributes() const
{
	if (GetAbilitySystemComponent() == nullptr) return;
	if (DefaultPrimaryAttributes == nullptr) return;
	
	FGameplayEffectContextHandle EffectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	//TODO 根据等级创建基础的GE值
	const FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultPrimaryAttributes,1,EffectContextHandle);
	//GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(),GetAbilitySystemComponent());
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}

