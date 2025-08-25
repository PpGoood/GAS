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

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Custom|Combat")
	TObjectPtr<USkeletalMeshComponent> WeaponMeshComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Custom|Combat")
	FName WeaponTipSocketName;

	//是否是受击状态
	UPROPERTY(BlueprintReadOnly, Category="Custom|Combat")
	bool bHitReacting = false; //当前是否处于被攻击状态

	UPROPERTY(BlueprintReadOnly, Category="Custom|Combat")
	float BaseWalkSpeed = 250.f; //当前角色的最大移动速度

	//和GAS相关
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	//使用GE对AttributeSet初始化
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Custom|Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Custom|Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Custom|Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	virtual void InitializeDefaultAttributes() const;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> EffectClass,float Level) const;

	virtual void InitCharacterAbilities();

	virtual FVector GetCombatSocketLocation() override;

	virtual void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
private:
	virtual void InitAbilityActorInfo(){};

	UPROPERTY(EditAnywhere,Category="Custom|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartAbilities;
};
