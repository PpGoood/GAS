// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Input/InputDataAsset.h"

const UInputAction* UInputDataAsset::FindAbilityInputActionByTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FGASInputAction& data : AbilityInputActions)
	{
		if (data.InputAction && data.InputTag == InputTag)
		{
			return data.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp,Error,TEXT("[peiLog]在 %s 里 %s 标签 没有被找到"),*InputTag.ToString(),*GetNameSafe(this));
	}
	return nullptr;
	
}
