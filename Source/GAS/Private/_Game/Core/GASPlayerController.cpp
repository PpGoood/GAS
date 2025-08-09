// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Core/GASPlayerController.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"

AGASPlayerController::AGASPlayerController()
{
	bReplicates = true;
}

void AGASPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(InputContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(InputContext,0);

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

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AGASPlayerController::Move);
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
