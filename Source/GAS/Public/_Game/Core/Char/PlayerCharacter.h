// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "_Game/Core/Char/GasCharacterBase.h"
#include "_Game/Interaction/CombatInterface.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GAS_API APlayerCharacter : public AGasCharacterBase
{
	GENERATED_BODY()
public:
	APlayerCharacter();
	virtual void PossessedBy(AController* NewController) override; //服务端初始化ASC
	virtual void OnRep_PlayerState() override; //客户端初始化ASC

	/** ICombatInterface **/
	virtual int32 GetPlayerLevel() override;
	/** ICombatInterface **/

private:
	virtual void InitAbilityActorInfo() override;
};
