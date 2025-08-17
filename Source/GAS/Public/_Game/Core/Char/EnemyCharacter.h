// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "_Game/Core/Char/GasCharacterBase.h"
#include "_Game/Interaction/CombatInterface.h"
#include "_Game/Interaction/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GAS_API AEnemyCharacter : public AGasCharacterBase,public IEnemyInterface,public ICombatInterface
{
	GENERATED_BODY()
	
public:
	AEnemyCharacter();
	
	/** EnemyInterface **/
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/** EnemyInterface **/

	/** CombatInterface **/
	virtual int32 GetPlayerLevel() override{return  Level;}
	/** CombatInterface **/
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Attributes")
	int32 Level = 1;
	
private:
	
	virtual void InitAbilityActorInfo() override;

};
