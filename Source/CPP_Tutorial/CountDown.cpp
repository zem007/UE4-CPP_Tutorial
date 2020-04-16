// Fill out your copyright notice in the Description page of Project Settings.


#include "CountDown.h"

// Sets default values
ACountDown::ACountDown()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountdownNumber"));
	CountdownText->SetHorizontalAlignment(EHTA_Center);
	CountdownText->SetWorldSize(150.0f);
	RootComponent = CountdownText;
	CountdownTime = 3;

}

// Called when the game starts or when spawned
void ACountDown::BeginPlay()
{
	Super::BeginPlay();
	//��ʹ��Tick��ʹ�ö�ʱ������ƣ�ÿ�����һ��AdvanceTimer����
	UpdateTimerDisplayer();
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACountDown::AdvanceTimer, 1.0f, true);
	
}

// Called every frame
void ACountDown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACountDown::UpdateTimerDisplayer() {
	CountdownText->SetText(FString::FromInt(FMath::Max(CountdownTime, 0)));
}

void ACountDown::AdvanceTimer() {
	CountdownTime--;
	UpdateTimerDisplayer();
	if (CountdownTime < 1) {
		//������ɣ�ֹͣ��ʱ���
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		CountdownHasFinished();
	}
}

void ACountDown::CountdownHasFinished_Implementation() {
	CountdownText->SetText(FText::FromString("GO GO GO!"));
}

