// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/InteractiveObject/EffectActor.h"

#include "AbilitySystemInterface.h"
#include "Components/SphereComponent.h"
#include "_Game/Core/AbilitySystem/MyAttributeSet.h"

// Sets default values
AEffectActor::AEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	SetRootComponent(SphereComponent);
	StaticMeshComponent->SetupAttachment(GetRootComponent());
}

void AEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: 为了测试数值修改功能，启用了常量转变量功能。
	if(IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		//根据类从ASC里面获取到对应的AS实例
		const UMyAttributeSet* AttributeSet = Cast<UMyAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UMyAttributeSet::StaticClass()));
		UMyAttributeSet* MutableAttributeSet = const_cast<UMyAttributeSet*>(AttributeSet); //将常量转为变量
		MutableAttributeSet->SetHealth(AttributeSet->GetHealth() + 25.f);
		Destroy(); // 销毁自身
	}
}

void AEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

// Called when the game starts or when spawned
void AEffectActor::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AEffectActor::OnOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AEffectActor::EndOverlap);

}


