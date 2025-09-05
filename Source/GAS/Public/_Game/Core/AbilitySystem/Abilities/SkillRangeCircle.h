// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillRangeCircle.generated.h"

UCLASS()
class GAS_API ASkillRangeCircle : public AActor
{
	GENERATED_BODY()

public:	
	ASkillRangeCircle();

	
protected:
	
	virtual void BeginPlay() override;



};
