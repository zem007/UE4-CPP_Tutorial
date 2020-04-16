// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "CountDown.generated.h"

UCLASS()
class CPP_TUTORIAL_API ACountDown : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACountDown();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		int32 CountdownTime;
	UTextRenderComponent* CountdownText;
	void UpdateTimerDisplayer();

	void AdvanceTimer();

	UFUNCTION(BlueprintNativeEvent)
		void CountdownHasFinished();
	virtual void CountdownHasFinished_Implementation();
	FTimerHandle CountdownTimerHandle;

};
