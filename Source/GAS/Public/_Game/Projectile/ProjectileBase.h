// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class GAS_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectileBase();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(BlueprintReadWrite,meta=( ExposeOnSpawn = true ))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;
protected:
	UPROPERTY(EditDefaultsOnly,Category="Projectiles|Properties")
	float LifeSpan = 5.f; 
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	virtual void Destroyed() override;
private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(EditAnywhere,category="Projectiles|Properties")
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	UPROPERTY(EditAnywhere,category="Projectiles|Properties")
	TObjectPtr<USoundBase> ImpactSound;

	UPROPERTY(EditAnywhere,category="Projectiles|Properties")
	TObjectPtr<USoundBase> LoopingSound;
	
	//储存循环音效的变量，后续用于删除
	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopingSoundComponent;
	
	void PlayImpact() const;

	bool bHit;
};
