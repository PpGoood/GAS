// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Core/Char/PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "_Game/Core/MyPlayerState.h"
#include "_Game/Core/AbilitySystem/MyAbilitySystemComponent.h"
#include "_Game/UI/HUD/MVCHUD.h"

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

	//由于弹簧臂没勾选了Inherit pitch，yaw，roll
	//弹簧臂不会随着玩家旋转即出生点有旋转角度则相机也不会旋转
	//所以playerstart的旋转必须和弹簧臂一致。
}
//服务器
void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
}
//客户端
void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();
}

int32 APlayerCharacter::GetPlayerLevel()
{
	AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	if (MyPlayerState == nullptr)return 0;

	return  MyPlayerState->GetPlayerLevel();
}

void APlayerCharacter::InitAbilityActorInfo()
{
	AMyPlayerState* MyPlayerState = GetPlayerState<AMyPlayerState>();
	check(MyPlayerState)
	AbilitySystemComponent = MyPlayerState->GetAbilitySystemComponent();
	AttributeSet = MyPlayerState->GetAttributeSet();
	AbilitySystemComponent->InitAbilityActorInfo(MyPlayerState,this);

	//获取PC
	if(APlayerController* PlayerControllerBase = Cast<APlayerController>(GetController()))
	{
		if(AMVCHUD* HUD = Cast<AMVCHUD>(PlayerControllerBase->GetHUD()))
		{
			HUD->InitControllerParams(PlayerControllerBase, MyPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	Cast<UMyAbilitySystemComponent>(AbilitySystemComponent)->InitAbilitySystemComponent();

	InitializeDefaultAttributes();
}
