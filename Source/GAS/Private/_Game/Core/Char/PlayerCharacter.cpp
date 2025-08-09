// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Core/Char/PlayerCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

APlayerCharacter::APlayerCharacter()
{
	//角色是否根据其移动方向来调整旋转
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//设置旋转速率
	GetCharacterMovement()->RotationRate = FRotator(0, 400.f, 0);
	//限制角色只在一个平面内进行移动
	GetCharacterMovement()->bConstrainToPlane = true;
	//当角色首次开始移动时，将其强制对齐到平面上
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}
