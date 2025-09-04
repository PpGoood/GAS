// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Data/WindAbilityDataAsset.h"
#include "GameFramework/Actor.h"
#include "WindDamageArea.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class GAS_API AWindDamageArea : public AActor
{
	GENERATED_BODY()
public:
	const float BUFF_EXTRA_BONUS = 1.4f;
	//球体的直径是200，用于范围和其比值得到缩放大小
	const float DIAMETER = 200.f;
	
	AWindDamageArea();

	//生成的时候暴露给外面的属性
	UPROPERTY(BlueprintReadWrite,meta=( ExposeOnSpawn = true ))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;
	
	UPROPERTY(BlueprintReadWrite,meta=( ExposeOnSpawn = true ))
	FWindChargeAbilityInfo WindChargeAbilityInfo;
	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TObjectPtr<USphereComponent> SphereComponent;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	virtual void Destroyed() override;
	
	UPROPERTY(BlueprintReadOnly)
	FVector TargetScale;

private:
	//用于集合记录已经碰撞操作到的物体避免重复碰撞
	TSet<AActor*> OverlapActors;

	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopingSoundComponent;
	
	UPROPERTY(EditAnywhere,category="Custom|Wind")
	TObjectPtr<USoundBase> LoopingSound;
};
