// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Core/GASPlayerController.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "_Game/Input/GASInputComponent.h"
#include "_Game/Interaction/EnemyInterface.h"

AGASPlayerController::AGASPlayerController()
{
	bReplicates = true;
}

void AGASPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(InputContext);
	
	UE_LOG(LogTemp, Warning, TEXT("This is running on %s with Role: %d"), 
	   *GetName(), (int)GetLocalRole());
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	
	if (Subsystem)
	{ 
		Subsystem->AddMappingContext(InputContext,0);
	}

	//显示鼠标
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	//鼠标不锁定 开始游戏后不隐藏能自由移动
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AGASPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//使用自定义的input组件，可以支持gameplaytag的触发
	UGASInputComponent* CustomInputComponent = CastChecked<UGASInputComponent>(InputComponent);
	CustomInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ThisClass::Move);
	//用自定义的DataAsset，让事件输入的时候可以转发标签
	CustomInputComponent->BindAbilityActions(InputDataAsset,this,&ThisClass::AbilityInputTagPressed,&ThisClass::AbilityInputTagReleased,&ThisClass::AbilityInputHeld);
}

void AGASPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CursorTrace();
}

void AGASPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);

	LastHighlightEnemy = CurHightlightEnemy;
	CurHightlightEnemy = Cast<IEnemyInterface>(CursorHit.GetActor());

	// 如果当前和上一个都没有敌人，直接返回
	if (CurHightlightEnemy == nullptr && LastHighlightEnemy == nullptr)
		return;

	// 如果当前没有敌人，但上一个敌人存在
	if (CurHightlightEnemy == nullptr)
	{
		LastHighlightEnemy->UnHighlightActor();
	}
	// 如果当前有敌人，但上一个敌人不存在
	else if (LastHighlightEnemy == nullptr)
	{
		CurHightlightEnemy->HighlightActor();
	}
	// 如果当前和上一个敌人都存在，且不同
	else if (CurHightlightEnemy != LastHighlightEnemy)
	{
		CurHightlightEnemy->HighlightActor();
		LastHighlightEnemy->UnHighlightActor();
	}
}

void AGASPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D Vector2 = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0,Rotation.Yaw,0);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControllerPawn = GetPawn<APawn>())
	{
		ControllerPawn->AddMovementInput(ForwardDirection, Vector2.Y);
		ControllerPawn->AddMovementInput(RightDirection,  Vector2.X);
	}
}

void AGASPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(1,3.f,FColor::Red,*InputTag.ToString());
}

void AGASPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(2,3.f,FColor::Blue,*InputTag.ToString());
}

void AGASPlayerController::AbilityInputHeld(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(3,3.f,FColor::Green,*InputTag.ToString());
}
