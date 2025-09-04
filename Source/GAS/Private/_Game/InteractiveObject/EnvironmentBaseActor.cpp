// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/InteractiveObject/EnvironmentBaseActor.h"
#include "Components/StaticMeshComponent.h"

AEnvironmentBaseActor::AEnvironmentBaseActor()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
}

void AEnvironmentBaseActor::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("MeshComponent"));
	SetRootComponent(MeshComponent);

	// 启用物理模拟
	MeshComponent->SetSimulatePhysics(true);

	// 设置箱子碰撞启用
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);  // 启用碰撞查询和物理模拟

	// 设置箱子碰撞响应
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Block);  // 对所有通道的响应为阻挡

	// 设置与特定通道的碰撞响应
	MeshComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);  // 对动态物体产生阻挡
	MeshComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);  // 对静态物体产生阻挡
	MeshComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);  // 对角色物体产生阻挡
}


void AEnvironmentBaseActor::KnockbackEffect(FVector Direction, float Strength)
{
	// 确保箱子启用了物理模拟
	if (MeshComponent->IsSimulatingPhysics())
	{
		// 施加击飞力
		MeshComponent->AddImpulse(Direction * Strength, NAME_None, true);  // 添加冲击力
	}
}


