// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Core/Char/EnemyCharacter.h"
#include "DrawDebugHelpers.h"
#include "GAS/GAS.h"
#include "Kismet/KismetSystemLibrary.h"

class UKismetSystemLibrary;

AEnemyCharacter::AEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
}

void AEnemyCharacter::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	WeaponMeshComponent->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	WeaponMeshComponent->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}


void AEnemyCharacter::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	WeaponMeshComponent->SetRenderCustomDepth(false);
}