// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GASBlueprintFunctionLibrary.generated.h"

class UAbilitySystemComponent;
enum class ECharacterClassType : uint8;
/**
 * 
 */
UCLASS()
class GAS_API UGASBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable,Category="GASAbilitySystemLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject,ECharacterClassType CharacterClass,float Level,UAbilitySystemComponent* ASC);
};
