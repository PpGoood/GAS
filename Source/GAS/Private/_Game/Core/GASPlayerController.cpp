// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Core/GASPlayerController.h"

#include "NavigationSystem.h"
#include "Components/SplineComponent.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "_Game/GameplayTagsInstance.h"
#include "_Game/Input/GASInputComponent.h"
#include "_Game/Interaction/EnemyInterface.h"
#include "NavigationPath.h"

AGASPlayerController::AGASPlayerController()
{
	bReplicates = true;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AGASPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
	AutoRun();
}

void AGASPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(InputContext);
	
	UE_LOG(LogTemp, Log, TEXT("[PeiLog]This is running on %s with Role: %d"), 
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
	//绑定Shift按键事件
	CustomInputComponent->BindAction(ShiftAction, ETriggerEvent::Started, this, &ThisClass::ShiftPressed);
	CustomInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &ThisClass::ShiftReleased);
	
	//用自定义的DataAsset，让事件输入的时候可以转发标签
	CustomInputComponent->BindAbilityActions(InputDataAsset,this,&ThisClass::AbilityInputTagPressed,&ThisClass::AbilityInputTagReleased,&ThisClass::AbilityInputTagHeld);
}

void AGASPlayerController::CursorTrace()
{
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);

	LastHighlightEnemy = CurHightlightEnemy;
	CurHightlightEnemy = Cast<IEnemyInterface>(CursorHit.GetActor());

	if(CurHightlightEnemy != LastHighlightEnemy)
	{
		if(CurHightlightEnemy) CurHightlightEnemy->HighlightActor();
		if(LastHighlightEnemy) LastHighlightEnemy->UnHighlightActor();
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

void AGASPlayerController::AbilityInputTagPressed(const FGameplayTag InputTag)
{
	if(InputTag.MatchesTagExact(GameplayTagsInstance::GetInstance().InputTag_LMB))
	{
		bTargeting = CurHightlightEnemy != nullptr; //为鼠标悬停在敌人身上才会有值
		bAutoRunning = false;
		FollowTime = 0.f; //重置统计的时间
	}
}

void AGASPlayerController::AbilityInputTagReleased(const FGameplayTag InputTag)
{
	if(!InputTag.MatchesTagExact(GameplayTagsInstance::GetInstance().InputTag_LMB))
	{
		if(GetMyAbilitySystemComponent()) GetMyAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
		return;
	}

	if(bTargeting || bShiftKeyDown)
	{
		if(GetMyAbilitySystemComponent()) GetMyAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
	}
	else
	{
		const APawn* ControlledPawn = GetPawn();
		if(FollowTime <= ShortPressThreshold && ControlledPawn)
		{
			//用自动寻路找到相关的点，将其放入到Spline中
			if(UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
			{
				Spline->ClearSplinePoints(); //清除样条内现有的点
				for(const FVector& PointLoc : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World); //将新的位置添加到样条曲线中
					DrawDebugSphere(GetWorld(), PointLoc, 8.f, 8, FColor::Orange, false, 5.f); //点击后debug调试
				}
				//自动寻路将最终目的地设置为导航的终点，方便停止导航
				if (NavPath->PathPoints.Num() > 0)
				{
					CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
					bAutoRunning = true; //设置当前正常自动寻路状态，将在tick中更新位置
				}
				else
				{
					// 处理数组为空的情况，例如设置默认值或返回错误
					UE_LOG(LogTemp, Warning, TEXT("[PeiLog]AGASPlayerController NavPath->PathPoints is empty!"));
					CachedDestination = FVector::ZeroVector; // 示例默认值
					bAutoRunning = false; //设置当前正常自动寻路状态，将在tick中更新位置
				}
			}
		}
	}
}

void AGASPlayerController::AbilityInputTagHeld(const FGameplayTag InputTag)
{
	if(!InputTag.MatchesTagExact(GameplayTagsInstance::GetInstance().InputTag_LMB))
	{
		if(GetMyAbilitySystemComponent()) GetMyAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
		return;
	}

	if(bTargeting || bShiftKeyDown)
	{
		if(GetMyAbilitySystemComponent()) GetMyAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds(); //统计悬停时间来判断是否为点击

		if(CursorHit.bBlockingHit) CachedDestination = CursorHit.ImpactPoint; //获取鼠标拾取位置

		if(APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}


void AGASPlayerController::AutoRun()
{
	if(!bAutoRunning) return;
	if(APawn* ControlledPawn = GetPawn())
	{
		//找到距离样条最近的位置
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		//获取这个位置在样条上的方向
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if(DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}