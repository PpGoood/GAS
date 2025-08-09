// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "_Game/Core/Char/GasCharacterBase.h"
#include "_Game/Interaction/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GAS_API AEnemyCharacter : public AGasCharacterBase,public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	AEnemyCharacter();
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

private:

};
