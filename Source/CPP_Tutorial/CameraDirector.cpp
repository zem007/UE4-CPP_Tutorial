// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"
#include "Kismet/GamePlayStatics.h"

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float TimeBetweenCameraChanges = 2.0f;
	const float SmoothBlendTime = 2.0f;
	TimeToNextCameraChange -= DeltaTime;
	if (TimeToNextCameraChange <= 0.0f) {
		//重置变换等待时间
		TimeToNextCameraChange += TimeBetweenCameraChanges;

		//查找处理本地玩家控制的Actor
		APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (OurPlayerController) {

			if (CameraOne != nullptr && OurPlayerController->GetViewTarget() != CameraOne) {
				OurPlayerController->SetViewTarget(CameraOne);
			}
			else if (CameraTwo != nullptr && OurPlayerController->GetViewTarget() != CameraTwo) {
				OurPlayerController->SetViewTargetWithBlend(CameraTwo);
			}
		}
	}

}
