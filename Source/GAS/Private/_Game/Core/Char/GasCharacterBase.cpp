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

void AGasCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultVitalAttributes,1);
	ApplyEffectToSelf(DefaultPrimaryAttributes,1);
	ApplyEffectToSelf(DefaultSecondaryAttributes,1);
}

void AGasCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> EffectClass, float Level) const
{
	if (GetAbilitySystemComponent() == nullptr) return;
	if (EffectClass == nullptr) return;
	
	FGameplayEffectContextHandle EffectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(EffectClass,Level,EffectContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}

