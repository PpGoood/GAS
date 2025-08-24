// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "_Game/Core/Char/GasCharacterBase.h"
#include "_Game/Interaction/CombatInterface.h"
#include "_Game/Interaction/EnemyInterface.h"
#include "_Game/UI/WidgetController/OverlayController.h"
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
	
	/** EnemyInterface **/
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/** EnemyInterface **/

	/** CombatInterface **/
	virtual int32 GetPlayerLevel() override{return  Level;}
	/** CombatInterface **/

	//接口
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Attributes")
	int32 Level = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Widget")
	TObjectPtr<UWidgetComponent> HealthBar;
private:
	
	virtual void InitAbilityActorInfo() override;
	void InitWidget();
	void BroadcastInitialValues();
	void BindCallbacksToDependencies();
};
