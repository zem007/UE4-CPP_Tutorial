// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnWithCamera.h"

// Sets default values
APawnWithCamera::APawnWithCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//�������,�ѵ��ɱۼ���������
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	OurCameraSpringArm->SetupAttachment(RootComponent);
	OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	OurCameraSpringArm->TargetArmLength = 400.0f;
	OurCameraSpringArm->bEnableCameraLag = true;
	OurCameraSpringArm->CameraLagSpeed = 3.0f;

	//����OurCamera��������������ڵ��ɱ������
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	OurCamera->SetupAttachment(OurCameraSpringArm, USpringArmComponent::SocketName);

	//��Pawn����ʱĬ���ɱ�����ҿ���
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void APawnWithCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnWithCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//����
	{
		if (bZoomingIn) {
			ZoomFactor += DeltaTime / 0.5f;
		}
		else {
			ZoomFactor -= DeltaTime / 0.25f;
		}
		ZoomFactor = FMath::Clamp(ZoomFactor, 0.0f, 1.0f);
		//����ZoomFactor�ı�����͵��ɱ�
		OurCamera->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
		OurCameraSpringArm->TargetArmLength = FMath::Lerp<float>(400.0f, 300.0f, ZoomFactor);
	}
	//��תActor��Yaw��������������丽������˽�ת�����
	{
		FRotator NewRotation = GetActorRotation();
		NewRotation.Yaw += CameraInput.X;
		SetActorRotation(NewRotation);
	}
	//��ת�����Pitch�����������ƣ�����Ӿ��̶�����
	{
		FRotator NewRotation = OurCameraSpringArm->GetComponentRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -80.0f, -15.0f);
		OurCameraSpringArm->SetWorldRotation(NewRotation);
	}

	{
		if (!MovementInput.IsZero()) {
			MovementInput = MovementInput.GetSafeNormal() * 100.0f;
			FVector NewLocation = GetActorLocation();
			NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
			NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
			SetActorLocation(NewLocation);
		}
	}
}

// Called to bind functionality to input
void APawnWithCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent); 

	//��ZoomIn����
	PlayerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &APawnWithCamera::ZoomIn);
	PlayerInputComponent->BindAction("ZoomIn", IE_Released, this, &APawnWithCamera::ZoomOut);

	//�����ĸ������֡����
	PlayerInputComponent->BindAxis("MoveForward", this, &APawnWithCamera::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APawnWithCamera::MoveRight);
	PlayerInputComponent->BindAxis("CameraPitch", this, &APawnWithCamera::PitchCamera);
	PlayerInputComponent->BindAxis("CameraYaw", this, &APawnWithCamera::YawCamera);

}

void APawnWithCamera::MoveRight(float AxisValue) {
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APawnWithCamera::MoveForward(float AxisValue) {
	MovementInput.X= FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APawnWithCamera::PitchCamera(float AxisValue) {
	CameraInput.X = AxisValue;
}

void APawnWithCamera::YawCamera(float AxisValue) {
	CameraInput.Y = AxisValue;
}

void APawnWithCamera::ZoomIn() {
	bZoomingIn = true;
}

void APawnWithCamera::ZoomOut() {
	bZoomingIn = false;
}
