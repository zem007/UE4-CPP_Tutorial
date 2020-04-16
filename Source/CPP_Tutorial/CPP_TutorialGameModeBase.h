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
	//移除当前控件，并在指定类(如果有)中新建控件
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	virtual void BeginPlay() override;

	//游戏开始时，用作菜单的控件类
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;

	//用作菜单的控件实例
	UPROPERTY()
		UUserWidget* CurrentWidget;
};
