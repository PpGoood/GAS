// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Core/AbilitySystem/Data/AttributeInfo.h"

FGASAttributeInfo UAttributeInfo::FindAttributeInfoByTag(const FGameplayTag AttributeTag, bool bLogNotFound) const
{
	for (const FGASAttributeInfo& Info : AttributeInformations)
	{
		if (Info.AttributeTag == AttributeTag)
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp,Error,TEXT("[peiLog]在 %s 里 %s 标签 没有被找到"),*AttributeTag.ToString(),*GetNameSafe(this));
	}
	return FGASAttributeInfo();
}
