// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameFramework/Actor.h"
#include "EffectActor.generated.h"


UENUM(BlueprintType) 
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap UMETA(DisplayName = "Apply on Overlap"),    
	ApplyOnEndOverlap UMETA(DisplayName = "Apply on End Overlap"), 
	None UMETA(DisplayName = "None")                   
};


UENUM(BlueprintType) 
enum class EEffectRemovalPolicy : uint8
{
	RemoveOnEndOverlap UMETA(DisplayName = "Remove on End Overlap"), 
	None UMETA(DisplayName = "None")
};

UENUM(BlueprintType) 
enum class EDestroyPolicy : uint8
{
	DestroyOnOverlap UMETA(DisplayName = "Destory on Overlap"),
	DestroyOnEndOverlap UMETA(DisplayName = "Destory on End Overlap"), 
	None UMETA(DisplayName = "None")
};


UCLASS()
class GAS_API AEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AEffectActor();

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable) 
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);//给与目标添加GameplayEffect

	//在重叠开始时处理效果的添加删除逻辑
	UFUNCTION(BlueprintCallable) 
	void OnOverlap(AActor* TargetActor);

	//在重叠结束时处理效果的添加删除逻辑
	UFUNCTION(BlueprintCallable) 
	void OnEndOverlap(AActor* TargetActor);

	//敌人是否能够拾取此物体
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Custom|Apply Effects")
	bool bApplyEffectsToEnemies = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Custom|Apply Effects")
	EDestroyPolicy DestroyPolicy = EDestroyPolicy::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Custom|Apply Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass; //生成GameplayEffect的类

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Custom|Apply Effects")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Custom|Apply Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass; //生成具有一定持续时间的GameplayEffect的类

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Custom|Apply Effects")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Custom|Apply Effects")
	TSubclassOf<UGameplayEffect> InfinityGameplayEffectClass; //生成具有一定持续时间的GameplayEffect的类

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Custom|Apply Effects")
	EEffectApplicationPolicy InfinityEffectApplicationPolicy = EEffectApplicationPolicy::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Custom|Apply Effects")
	EEffectRemovalPolicy InfinityEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;

	//用于存储当前已经激活的GameplayEffect的句柄的map
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Custom|Apply Effects")
	float ActorLevel = 1.f;
};
