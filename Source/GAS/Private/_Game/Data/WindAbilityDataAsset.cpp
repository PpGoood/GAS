// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Data/WindAbilityDataAsset.h"

FWindChargeAbilityInfo UWindAbilityDataAsset::FindChargeAbilityInfo(EWindChargeType Type)
{
	for (const FWindChargeAbilityInfo& AbilityInfo : ChargeAbilityInfos)
	{
		if (AbilityInfo.ChargeType == Type)
		{
			return AbilityInfo;
		}
	}
	return FWindChargeAbilityInfo();
}

FWindChargeAbilityInfo UWindAbilityDataAsset::FindChargeAbilityInfoByTime(float ChargeTime)
{
	for (const FWindChargeAbilityInfo& AbilityInfo : ChargeAbilityInfos)
	{
		if (ChargeTime < AbilityInfo.ChargeTime)
		{
			return AbilityInfo;
		}
	}
	return FWindChargeAbilityInfo();
}

