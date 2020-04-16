// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//���������
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	//�������
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	//�����ɼ���̬���������
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	//���������Ϳɼ���̬������������븽�ӵ��������ƫ�Ʋ���ת���
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

	//���ݡ�Grow�����룬���ı�bGrowing������ÿ֡����������Scale
	{
		float CurrentScale = OurVisibleComponent->GetComponentScale().X;
		if (bGrowing) {
			//һ������������С
			CurrentScale += DeltaTime;
		}
		else {
			//����һ��
			CurrentScale -= (DeltaTime * 0.5f);
		}
		//ȷ��Scale���ŷ�Χ��ԭʼ��С��������С֮��
		CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
		OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale)); //�����FVector��֤ÿ�������ǰ�ͬ����������

	}

	//���ݡ�MoveX���͡�MoveY���������ƶ������ı�CurrentVelocity������ÿ֡�ƶ�
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
	//���»��ɿ���Grow�����ո����ʱ������Ӧ
	PlayerInputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing);
	PlayerInputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);

	//�����ƶ��ᡰMoveX����W��S�����͡�MoveY����A��D����ʱ��������Ӧ
	PlayerInputComponent->BindAxis("MoveX", this, &AMyPawn::Move_XAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &AMyPawn::Move_YAxis);
}

//�����ĸ������Ƕ����������Ӧ��������Ҫ������İ����������а�bind
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

