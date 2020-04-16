// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//创建根组件
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	//创建相机
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	//创建可见静态网格体组件
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	//将相机组件和可见静态网格体组件放入附加到根组件，偏移并旋转相机
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	OurVisibleComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//根据“Grow”输入，来改变bGrowing，进而每帧增长或缩减Scale
	{
		float CurrentScale = OurVisibleComponent->GetComponentScale().X;
		if (bGrowing) {
			//一秒增长两倍大小
			CurrentScale += DeltaTime;
		}
		else {
			//缩减一倍
			CurrentScale -= (DeltaTime * 0.5f);
		}
		//确保Scale缩放范围在原始大小和两倍大小之间
		CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
		OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale)); //这里的FVector保证每个方向都是按同比例放缩的

	}

	//根据“MoveX”和“MoveY”来处理移动，来改变CurrentVelocity，进而每帧移动
	{
		if (!CurrentVelocity.IsZero()) {
			FVector Newlocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
			SetActorLocation(Newlocation);
		}
	}

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//按下或松开“Grow”（空格键）时做出相应
	PlayerInputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing);
	PlayerInputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);

	//按下移动轴“MoveX”（W或S键）和“MoveY”（A或D键）时做出的响应
	PlayerInputComponent->BindAxis("MoveX", this, &AMyPawn::Move_XAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &AMyPawn::Move_YAxis);
}

//下面四个函数是定义的输入响应函数，需要和上面的按键函数进行绑定bind
void AMyPawn::Move_XAxis(float AxisValue) {
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::Move_YAxis(float AxisValue) {
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::StartGrowing() {
	bGrowing = true;
}

void AMyPawn::StopGrowing() {
	bGrowing = false;
}

