// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Core/AbilitySystem/Data/CharacterClassInfo.h"

FCharacterClassDefaultInfo UCharacterClassInfo::GetClassDefaultInfo(ECharacterClassType CharacterClass)
{
	return CharacterClassInformation.FindChecked(CharacterClass);
}
