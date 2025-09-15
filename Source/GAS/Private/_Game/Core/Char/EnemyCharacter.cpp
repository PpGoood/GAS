// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Core/Char/EnemyCharacter.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "GAS/GAS.h"
#include "_Game/Core/AbilitySystem/MyAbilitySystemComponent.h"
#include "_Game/Core/AbilitySystem/MyAttributeSet.h"
#include "_Game/Util/GASBlueprintFunctionLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	GetMesh()->SetEnableGravity(true); //开启重力效果
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	//初始化GAS组件
	AbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UMyAttributeSet>(TEXT("AttributeSet"));

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
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

void AEnemyCharacter::KnockbackEffect(FVector Direction, float Strength)
{
	FVector KnockbackVector = Direction * Strength;
	UE_LOG(LogTemp, Log, TEXT("[PeiLog]Launch Velocity: %s"), *KnockbackVector.ToString());
	LaunchCharacter(KnockbackVector,true,true);
}

void AEnemyCharacter::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}

AActor* AEnemyCharacter::GetCombatTarget_Implementation() const
{
	return CombatTarget;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilityActorInfo();
	InitBindEvent();
	//初始化属性和技能都走的AssetData
	InitDefaultAttributes();
	InitDefaultAbilities();
	//加载血条
	InitWidget();
}

void AEnemyCharacter::InitDefaultAttributes() const
{
	if (!HasAuthority())return;
	UGASBlueprintFunctionLibrary::InitializeDefaultAttributes(this,CharacterClassType,Level,AbilitySystemComponent);
}

void AEnemyCharacter::InitDefaultAbilities()
{
	if (!HasAuthority())return;
	UGASBlueprintFunctionLibrary::GiveStartupAbilities(this, AbilitySystemComponent,CharacterClassType);
}

void AEnemyCharacter::Die()
{
	SetLifeSpan(LifeSpan);
	if(GASAIController) GASAIController->GetBlackboardComponent()->SetValueAsBool(FName("Dead"), true); //设置死亡，停止AI行为树
	Super::Die();
}

void AEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if(!HasAuthority()) return;
	//AIController是在服务器端执行的，所以需要在PossessedBy函数回调中获取服务器返回
	GASAIController = Cast<AGASAIController>(NewController);
	//初始化行为树上设置的黑板
	GASAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	//运行行为树
	GASAIController->RunBehaviorTree(BehaviorTree);

	GASAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"),false);
	GASAIController->GetBlackboardComponent()->SetValueAsBool(FName("MeleeAttacker"),CharacterClassType == ECharacterClassType::Warrior);
}

void AEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	Cast<UMyAbilitySystemComponent>(AbilitySystemComponent)->InitAbilitySystemComponent();
}

void AEnemyCharacter::InitWidget()
{
	if(UMVCWidget* UserWidget = Cast<UMVCWidget>(HealthBar->GetUserWidgetObject()))
	{
		UserWidget->SetWidgetController(this);
		BroadcastInitialValues();
		BindCallbacksToDependencies();
	}
}

void AEnemyCharacter::BroadcastInitialValues()
{
	const UMyAttributeSet* AttributeSetBase = CastChecked<UMyAttributeSet>(AttributeSet);
	if (AttributeSetBase == nullptr)return;
	
	OnHealthChanged.Broadcast(AttributeSetBase->GetHealth());
	OnMaxHealthChanged.Broadcast(AttributeSetBase->GetMaxHealth());
}

void AEnemyCharacter::BindCallbacksToDependencies()
{
	const UMyAttributeSet* AttributeSetBase = CastChecked<UMyAttributeSet>(AttributeSet);
	if (AttributeSetBase == nullptr)return;
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttributeSetBase->GetHealthAttribute()).AddLambda( [this](const FOnAttributeChangeData& Data){
			UE_LOG(LogTemp, Display, TEXT("[PeiLog]Health Changed %f"), Data.NewValue);
			OnHealthChanged.Broadcast(Data.NewValue);
		});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttributeSetBase->GetMaxHealthAttribute()).AddLambda( [this](const FOnAttributeChangeData& Data){
			OnMaxHealthChanged.Broadcast(Data.NewValue);  
		});

}

void AEnemyCharacter::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	Super::HitReactTagChanged(CallbackTag, NewCount);
	if (GASAIController && GASAIController->GetBlackboardComponent())
	{
		GASAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"),bHitReacting);
	}
}