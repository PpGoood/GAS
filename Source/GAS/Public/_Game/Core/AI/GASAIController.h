// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GASAIController.generated.h"

class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class GAS_API AGASAIController : public AAIController
{
	GENERATED_BODY()

public:
	AGASAIController();

protected:

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};
