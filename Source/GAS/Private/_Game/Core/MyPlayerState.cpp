// Fill out your copyright notice in the Description page of Project Settings.

#include "_Game/Core/MyPlayerState.h"

#include "Net/UnrealNetwork.h"
#include "_Game/Core/AbilitySystem/MyAbilitySystemComponent.h"
#include "_Game/Core/AbilitySystem/MyAttributeSet.h"

AMyPlayerState::AMyPlayerState()
{
	// 这个Actor每秒向客户端发送状态更新的最大次数为100次
	NetUpdateFrequency = 100.f;

	//初始化GAS组件
	AbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UMyAttributeSet>(TEXT("AttributeSet"));
}

void AMyPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(AMyPlayerState, Level, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME(AMyPlayerState,Level);
}

void AMyPlayerState::OnRep_Level(int32 OldLevel)
{
	
}
