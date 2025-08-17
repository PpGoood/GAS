// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

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

	FORCEINLINE int32 GetPlayerLevel() const {return Level;}
protected:
	//和GAS相关
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

private:
	
	UPROPERTY(VisibleAnywhere,ReplicatedUsing = OnRep_Level, Category="Attributes")
	int32 Level = 1;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);
};
