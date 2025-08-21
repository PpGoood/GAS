// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "_Game/Interaction/CombatInterface.h"
#include "GasCharacterBase.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;

UCLASS(Abstract)
class GAS_API AGasCharacterBase : public ACharacter,public IAbilitySystemInterface,public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGasCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override {return AbilitySystemComponent;}
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Combat")
	TObjectPtr<USkeletalMeshComponent> WeaponMeshComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Combat")
	FName WeaponTipSocketName;

	//和GAS相关
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	//使用GE对AttributeSet初始化
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	void InitializeDefaultAttributes() const;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> EffectClass,float Level) const;

	void AddCharacterAbilities();

	virtual FVector GetCombatSocketLocation() override;
private:
	virtual void InitAbilityActorInfo(){};

	UPROPERTY(EditAnywhere,Category="Attributes|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartAbilities;
};
