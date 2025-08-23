// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/MyAbilitySystemComponent.h"
#include "Char/GasCharacterBase.h"
#include "GameFramework/PlayerController.h"
#include "_Game/Interaction/EnemyInterface.h"
#include "GASPlayerController.generated.h"

class USplineComponent;
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
	//PlayerTick只能用于本地Controller，不能用于服务端和非本地的Controller；Tick则不受限制。
	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> InputContext;

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> ShiftAction;
	void ShiftPressed() { bShiftKeyDown = true; };
	void ShiftReleased() { bShiftKeyDown = false; };
	bool bShiftKeyDown = false;
	
	
	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UInputDataAsset> InputDataAsset;

	void Move(const struct FInputActionValue& InputActionValue);

	void CursorTrace();
	IEnemyInterface* LastHighlightEnemy = nullptr;
	IEnemyInterface* CurHightlightEnemy = nullptr;
	FHitResult CursorHit; //鼠标拾取结果，可以复用

	/**
	 * Ability
	 */
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);

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

	/**
	 * 用鼠标控制移动
	 */
	FVector CachedDestination = FVector::ZeroVector; //存储鼠标点击的位置
	float FollowTime = 0.f; // 用于查看按住了多久
	bool bAutoRunning = false; //当前是否自动移动
	bool bTargeting = false; //当前鼠标是否选中敌人

	UPROPERTY(EditDefaultsOnly)
	float ShortPressThreshold = 0.3f; //定义鼠标悬停多长时间内算点击事件

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f; //当角色和目标距离在此半径内时，将关闭自动寻路

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline; //自动寻路时生成的样条线

	void AutoRun();
};
