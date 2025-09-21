// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "_Game/Data/LevelUpDataAsset.h"
#include "MyPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStateChanged, int32);

class UAttributeSet;
/**
 * 
 */
UCLASS()
class GAS_API AMyPlayerState : public APlayerState,public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:

	AMyPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override {return AbilitySystemComponent;}
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}

	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpDataAsset> LevelUpInfo; //设置升级相关数据
	
	FOnPlayerStateChanged OnXPChangedDelegate; //经验值变动委托
	FOnPlayerStateChanged OnLevelChangedDelegate; //等级变动委托

	FORCEINLINE int32 GetPlayerLevel() const {return Level;} //获取角色等级
	void AddToLevel(int32 InLevel); //增加等级
	void SetLevel(int32 InLevel); //设置当前等级

	FORCEINLINE int32 GetXP() const {return XP;} //获取角色当前经验值
	void AddToXP(int32 InXP); //增加经验值
	void SetXP(int32 InXP); //设置当前经验值
protected:
	//和GAS相关
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
private:

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Level)
	int32 Level = 1.f;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_XP)
	int32 XP = 0.f;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel) const; //服务器出现更改自动同步到本地函数 等级

	UFUNCTION()
	void OnRep_XP(int32 OldXP) const; //服务器出现更改自动同步到本地函数 经验值

};

