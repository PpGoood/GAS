// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Projectile/ProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(FName("Sphere"));
	SetRootComponent(SphereComponent);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_WorldDynamic,ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovementComponent"));
	
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	//设置物体存在的时间
	SetLifeSpan(LifeSpan);
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&ThisClass::OnSphereOverlap);

	//添加一个音效，并附加到根组件上面，在技能移动时，声音也会跟随移动
	LoopingSoundComponent = UGameplayStatics::SpawnSoundAttached(LoopingSound, GetRootComponent());
}

void AProjectileBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	PlayImpact();

	//在重叠后，销毁自身
	if(HasAuthority())
	{
		Destroy();
	}
	else
	{
		//如果对actor没有权威性，将bHit设置为true，证明当前已经播放了击中特效
		bHit = true;
	}
}

void AProjectileBase::Destroyed()
{
	//如果没有权威性，并且bHit没有修改为true，证明当前没有触发Overlap事件，在销毁前播放击中特效
	if(!bHit && !HasAuthority())
	{
		PlayImpact();
	}
	Super::Destroyed();
}

void AProjectileBase::PlayImpact() const
{
	check(ImpactSound);
	check(ImpactEffect);
	//播放音效
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
	//播放粒子特效
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
	//将音乐停止后会自动销毁
	//如果我们添加的是循环播放的音效，它无法被停止，所以，我们将在火球术结束时，将音效组件暂停。创建的附加音效默认会在音效播放完成或者暂停后自动销毁。
	if(LoopingSoundComponent) LoopingSoundComponent->Stop();
}


