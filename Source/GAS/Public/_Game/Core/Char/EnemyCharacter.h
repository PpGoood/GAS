// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "_Game/Core/AbilitySystem/Data/CharacterClassInfo.h"
#include "_Game/Core/Char/GasCharacterBase.h"
#include "_Game/Interaction/CombatInterface.h"
#include "_Game/Interaction/EnemyInterface.h"
#include "_Game/UI/WidgetController/OverlayController.h"
#include "EnemyCharacter.generated.h"

enum class ECharacterClassType : uint8;
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
	
	UPROPERTY(BlueprintAssignable, Category="Custom|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="Custom|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Custom|Attributes")
	ECharacterClassType CharacterClassType = ECharacterClassType::Warrior;
	
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Custom|Attributes")
	int32 Level = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Custom|Widget")
	TObjectPtr<UWidgetComponent> HealthBar;
	
	virtual void InitAbilityActorInfo() override;
	virtual void InitDefaultAttributes() const override;
	virtual void InitDefaultAbilities() override;

private:
	void InitWidget();
	void BroadcastInitialValues();
	void BindCallbacksToDependencies();
};
