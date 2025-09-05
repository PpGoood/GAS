// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/WindDamageArea.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "_Game/GameplayTagsInstance.h"
#include "_Game/Interaction/EnemyInterface.h"
#include "_Game/InteractiveObject/EnvironmentBaseActor.h"

AWindDamageArea::AWindDamageArea()
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
}

void AWindDamageArea::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&ThisClass::OnSphereOverlap);
	LoopingSoundComponent = UGameplayStatics::SpawnSoundAttached(ActiveSound, GetRootComponent());
	// UGameplayStatics::PlaySoundAtLocation(this, ActiveSound, GetActorLocation(), FRotator::ZeroRotator);
	
	const float Scale = WindChargeAbilityInfo.Range / DIAMETER;
	TargetScale.Set(Scale,Scale,Scale);
	
	SphereComponent->SetWorldScale3D(FVector(0.0f, 0.0f, 0.0f));
}

void AWindDamageArea::EffectToActor(AActor* Actor)
{
	if (!HasAuthority())return;
	if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor))
	{
		//有组件的受伤害
		TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
		if (DebuffEffectSpecHandle != nullptr)
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*DebuffEffectSpecHandle.Data.Get());
		}
	}
}

void AWindDamageArea::OnSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlapActors.Contains(OtherActor))return;
	OverlapActors.Add(OtherActor);
	if (OtherActor == GetInstigator())return;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Wind碰撞到了"));  // 输出在屏幕上

	EffectToActor(OtherActor);

	// 计算风源位置与目标（Environment）位置之间的向量
	FVector WindSourceLocation = GetActorLocation();  // WindDamageArea 的位置
	FVector TargetLocation = OtherActor->GetActorLocation();  // 环境物体的位置

	// 计算反向向量
	FVector KnockbackDirection = TargetLocation - WindSourceLocation;
	KnockbackDirection.Normalize();  

	const GameplayTagsInstance& TagsInstance = GameplayTagsInstance::GetInstance();
	
	if (OtherActor->ActorHasTag(FName("Enemy")))
	{
		// if (IEnemyInterface* EnemyInterface = Cast<IEnemyInterface>(OtherActor))
		// {
		// 	EnemyInterface->KnockbackEffect(KnockbackDirection,WindChargeAbilityInfo.WindStrength);
		// }
		if (ACharacter* Character = Cast<ACharacter>(OtherActor))
		{
			//TODO 暂时写法
			Character->LaunchCharacter(KnockbackDirection * WindChargeAbilityInfo.WindStrength*2,true,true);
		}
	}
	AEnvironmentBaseActor* Environment = Cast<AEnvironmentBaseActor>(OtherActor);
	if (Environment == nullptr)return;

	switch (WindChargeAbilityInfo.ChargeType)
	{
		case EWindChargeType::Light:
			if (Environment->EnvironmentTag.MatchesTagExact(TagsInstance.Environment_LightObject))
			{
				Environment->KnockbackEffect(KnockbackDirection,WindChargeAbilityInfo.WindStrength);
			}
			break;
		case EWindChargeType::Medium:
		case EWindChargeType::Full:
			if (Environment->EnvironmentTag.MatchesTagExact(TagsInstance.Environment_LightObject) ||
				Environment->EnvironmentTag.MatchesTagExact(TagsInstance.Environment_MediumObject))
			{
				Environment->KnockbackEffect(KnockbackDirection,WindChargeAbilityInfo.WindStrength);
			}
			break;
		default:
			break;
	}
	
}

void AWindDamageArea::Destroyed()
{
	Super::Destroyed();
	if(LoopingSoundComponent) LoopingSoundComponent->Stop();
}



