// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "_Game/Core/AbilitySystem/Data/CharacterClassInfo.h"
#include "_Game/Core/AI/GASAIController.h"
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
	virtual void KnockbackEffect(FVector Direction, float Strength = 100) override;
	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual AActor* GetCombatTarget_Implementation() const override;
	/** EnemyInterface **/

	/** CombatInterface **/
	virtual int32 GetPlayerLevel_Implementation() override{return Level;}
	/** CombatInterface **/
	
	UPROPERTY(BlueprintAssignable, Category="Custom|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="Custom|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;

protected:
	
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Custom|Attributes")
	int32 Level = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Custom|Widget")
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditAnywhere, Category="Custom|AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	UPROPERTY()
	TObjectPtr<AGASAIController> GASAIController;

	virtual void PossessedBy(AController* NewController) override;
	virtual void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount) override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitDefaultAttributes() const override;
	virtual void InitDefaultAbilities() override;

	virtual void Die() override;

private:
	void InitWidget();
	void BroadcastInitialValues();
	void BindCallbacksToDependencies();

	TObjectPtr<AActor> CombatTarget;
};


