// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "CPP_TutorialGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CPP_TUTORIAL_API ACPP_TutorialGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	//�Ƴ���ǰ�ؼ�������ָ����(�����)���½��ؼ�
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	virtual void BeginPlay() override;

	//��Ϸ��ʼʱ�������˵��Ŀؼ���
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;

	//�����˵��Ŀؼ�ʵ��
	UPROPERTY()
		UUserWidget* CurrentWidget;
};
