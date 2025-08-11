// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/InteractiveObject/EffectActor.h"

#include "AbilitySystemInterface.h"
#include "_Game/Core/AbilitySystem/MyAttributeSet.h"

// Sets default values
AEffectActor::AEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}


void AEffectActor::BeginPlay()
{
	Super::BeginPlay();

}

void AEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(TargetActor);
	if (ASCInterface == nullptr)return;

	UAbilitySystemComponent* AbilitySystemComponent = ASCInterface->GetAbilitySystemComponent();
	
	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}


