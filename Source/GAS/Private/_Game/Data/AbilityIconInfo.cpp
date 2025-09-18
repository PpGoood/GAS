// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Data/AbilityIconInfo.h"

FGASAbilityIconInfo UAbilityIconInfo::FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound) const
{
	for(const FGASAbilityIconInfo& Info : AbilityInformation)
	{
		if(Info.AbilityTag == AbilityTag)
		{
			return Info;
		}
	}

	if(bLogNotFound)
	{
		//如果获取不到数据，打印消息
	}

	return FGASAbilityIconInfo();
}
