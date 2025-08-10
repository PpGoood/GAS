// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Core/Char/EnemyCharacter.h"
#include "DrawDebugHelpers.h"
#include "GAS/GAS.h"
#include "_Game/Core/AbilitySystem/MyAbilitySystemComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);

	//初始化GAS组件
	AbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UAttributeSet>(TEXT("AttributeSet"));
}

void AEnemyCharacter::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	WeaponMeshComponent->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	WeaponMeshComponent->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}


void AEnemyCharacter::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	WeaponMeshComponent->SetRenderCustomDepth(false);
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this,this);
}
