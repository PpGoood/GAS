// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagAssetInterface.h"
#include "GameFramework/Actor.h"
#include "EnvironmentBaseActor.generated.h"



UCLASS()
class GAS_API AEnvironmentBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnvironmentBaseActor();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,category="Custom|Environment")
	FGameplayTag EnvironmentTag;
	
	virtual void KnockbackEffect(FVector Direction, float Strength = 100);

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,category="Custom|Environment")
	TObjectPtr<UStaticMeshComponent> MeshComponent;
};
