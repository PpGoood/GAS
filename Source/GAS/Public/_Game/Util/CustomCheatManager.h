// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "CustomCheatManager.generated.h"

/**
 * 
 */
UCLASS()
class GAS_API UCustomCheatManager : public UCheatManager
{
	GENERATED_BODY()

public:
	UFUNCTION(Exec)
	void AddWindMastery();

	UFUNCTION(Exec)
	void ForceGust(int Level = 1);

	UFUNCTION(Exec)
	void ResetRingCooldown();
};
