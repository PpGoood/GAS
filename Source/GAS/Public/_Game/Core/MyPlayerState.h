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
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}
protected:
	//和GAS相关
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
