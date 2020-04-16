// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "CPP_TutorialGameModeBase.h"

void ACPP_TutorialGameModeBase::BeginPlay() {
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);
}

void ACPP_TutorialGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass) {
	if (CurrentWidget != nullptr) {
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr) {
		//�����˵��ؼ�ʵ��
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr) {
			CurrentWidget->AddToViewport();
		}
	}
}
