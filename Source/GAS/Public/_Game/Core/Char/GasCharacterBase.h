// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "_Game/Interaction/CombatInterface.h"
#include "GasCharacterBase.generated.h"

struct FGameplayTag;
class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;

UCLASS(Abstract)
class GAS_API AGasCharacterBase : public ACharacter,public IAbilitySystemInterface,public ICombatInterface
{
	GENERATED_BODY()

public:
	AGasCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override {return AbilitySystemComponent;}
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}

	/** CombatInterface **/
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	virtual FVector GetCombatSocketLocation_Implementation() override;
	virtual void Die() override;
	virtual AActor* GetAvatar_Implementation() override;
	virtual bool IsDead_Implementation() const override;
	virtual TArray<FTaggedMontage> GetAttackMontageInfo_Implementation() override;
	virtual FVector GetCombatSocketLocationByInfo_Implementation(const FTaggedMontage TaggedMontage) const override;
	/** CombatInterface **/
	 
protected:
	//和GAS相关
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	//战斗
	bool bDead = false;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Custom|Combat")
	TObjectPtr<USkeletalMeshComponent> WeaponMeshComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Custom|Combat")
	FName WeaponTipSocketName;

	UPROPERTY(EditAnywhere, Category="Custom|Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;

	//死亡溶解相关材质
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Custom|Combat")
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Custom|Combat")
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;

	//是否是受击状态
	UPROPERTY(BlueprintReadOnly, Category="Custom|Combat")
	bool bHitReacting = false; //当前是否处于被攻击状态

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Custom|Combat")
	float BaseWalkSpeed = 250.f; //当前角色的最大移动速度
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Custom|Combat")
	float LifeSpan = 5.f;

	UPROPERTY(EditAnywhere, Category="Custom|Combat")
	TArray<FTaggedMontage> AttackMontageInfo;

	//使用GE对AttributeSet初始化
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Custom|Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Custom|Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Custom|Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(EditAnywhere,Category="Custom|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartAbilities;
	
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> EffectClass,float Level) const;

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath();
	
	virtual void BeginPlay() override;
	
	virtual void InitAbilityActorInfo(){};

	virtual void InitBindEvent();
	
	virtual void InitDefaultAttributes() const;
	
	virtual void InitDefaultAbilities();

	virtual void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	//用蓝图实现时间轴溶解此逻辑不在c++做
	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(const TArray<UMaterialInstanceDynamic*>& DynamicMaterialInstance);
	
	void Dissolve(); //溶解效果
	
};
