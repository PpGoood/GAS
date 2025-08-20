// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "InputDataAsset.h"
#include "GASInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class GAS_API UGASInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<typename UserClass,typename PressedFuncType,typename ReleasedFunctype,typename HeldFuncType>
	void BindAbilityActions(const UInputDataAsset* InputDataAsset,UserClass* Object,PressedFuncType PressedFunc,ReleasedFunctype ReleasedFunc,HeldFuncType HeldFunc);
};

//controller绑定，每个action有对应的tag，触发的时候会触发Controller里面的三个回调方法转发tag，这样实现了按下哪个键触发了一个然后能够去知道这个键在什么时候按下触发的什么inputtag
template <typename UserClass, typename PressedFuncType, typename ReleasedFunctype, typename HeldFuncType>
void UGASInputComponent::BindAbilityActions(const UInputDataAsset* InputDataAsset, UserClass* Object,
PressedFuncType PressedFunc, ReleasedFunctype ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputDataAsset);

	for (const FGASInputAction& Data : InputDataAsset->AbilityInputActions)
	{
		if (Data.InputAction == nullptr || !Data.InputTag.IsValid())
		{
			return;
		}

		if (PressedFunc)
		{
			BindAction(Data.InputAction,ETriggerEvent::Started,Object,PressedFunc,Data.InputTag);
		}

		if (ReleasedFunc)
		{
			BindAction(Data.InputAction,ETriggerEvent::Completed,Object,ReleasedFunc,Data.InputTag);
		}
		
		if (HeldFunc)
		{
			BindAction(Data.InputAction,ETriggerEvent::Triggered,Object,HeldFunc,Data.InputTag);
		}		
	}
}
