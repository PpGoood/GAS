// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/MyAbilitySystemComponent.h"
#include "Char/GasCharacterBase.h"
#include "GameFramework/PlayerController.h"
#include "_Game/Interaction/EnemyInterface.h"
#include "GASPlayerController.generated.h"

class AGasCharacterBase;
struct FGameplayTag;
class UInputDataAsset;
class IEnemyInterface;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class GAS_API AGASPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AGASPlayerController();
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
private:
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> InputContext;

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UInputDataAsset> InputDataAsset;

	void CursorTrace();
	IEnemyInterface* LastHighlightEnemy;
	IEnemyInterface* CurHightlightEnemy;
	
	void Move(const struct FInputActionValue& InputActionValue);

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputHeld(FGameplayTag InputTag);

	UPROPERTY()
	TObjectPtr<UMyAbilitySystemComponent> MyAbilitySystemComponent;

	UMyAbilitySystemComponent* GetMyAbilitySystemComponent()
	{
		if (MyAbilitySystemComponent != nullptr)
		{
			return MyAbilitySystemComponent;
		}

		MyAbilitySystemComponent = Cast<UMyAbilitySystemComponent>(GetPawn<AGasCharacterBase>()->GetAbilitySystemComponent());
		return MyAbilitySystemComponent;
	};
};
