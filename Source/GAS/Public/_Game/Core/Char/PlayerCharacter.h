// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "_Game/Core/Char/GasCharacterBase.h"
#include "_Game/Interaction/CombatInterface.h"
#include "_Game/Interaction/PlayerInterface.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GAS_API APlayerCharacter : public AGasCharacterBase,public IPlayerInterface
{
	GENERATED_BODY()
public:
	APlayerCharacter();
	virtual void PossessedBy(AController* NewController) override; //服务端初始化ASC
	virtual void OnRep_PlayerState() override; //客户端初始化ASC

	/** ICombatInterface **/
	virtual int32 GetPlayerLevel_Implementation() override;
	/** ICombatInterface **/

	/** IPlayerInterface **/
	virtual void AddToXP_Implementation(int32 InXP) override;
	virtual void LevelUp_Implementation() override;
	virtual int32 GetXP_Implementation() const override;
	virtual int32 FindLevelForXP_Implementation(int32 InXP) const override;
	virtual int32 GetAttributePointsReward_Implementation(int32 Level) const override;
	virtual int32 GetSpellPointsReward_Implementation(int32 Level) const override;
	virtual void AddToPlayerLevel_Implementation(int32 InPlayerLevel) override;
	virtual void AddToAttributePoints_Implementation(int32 InAttributePoints) override;
	virtual void AddToSpellPoints_Implementation(int32 InSpellPoints) override;
	/** IPlayerInterface **/

	virtual void InitAbilityActorInfo() override;
private:
	void InitDefault();
};
