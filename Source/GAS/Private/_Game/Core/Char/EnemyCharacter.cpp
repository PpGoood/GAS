// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Core/Char/EnemyCharacter.h"
#include "DrawDebugHelpers.h"
#include "GAS/GAS.h"
#include "_Game/Core/AbilitySystem/MyAbilitySystemComponent.h"
#include "_Game/Core/AbilitySystem/MyAttributeSet.h"
#include "_Game/Util/GASBlueprintFunctionLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);

	//初始化GAS组件
	AbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UMyAttributeSet>(TEXT("AttributeSet"));

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
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

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilityActorInfo();
	//初始化属性和技能都走的AssetData
	InitializeDefaultAttributes();
	InitCharacterAbilities();
	//加载血条
	InitWidget();
}

void AEnemyCharacter::InitializeDefaultAttributes() const
{
	UGASBlueprintFunctionLibrary::InitializeDefaultAttributes(this,CharacterClassType,Level,AbilitySystemComponent);
}

void AEnemyCharacter::InitCharacterAbilities()
{
	UGASBlueprintFunctionLibrary::GiveStartupAbilities(this, AbilitySystemComponent);
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
