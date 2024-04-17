// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

class ARotateActor;

UCLASS()
class TP_POINTSCREEN_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;

	ARotateActor* RotateActor;

	void OnDotReceived(const FVector2D, const FVector2D, const FVector2D, const FVector2D, const bool);
	
	UFUNCTION(BlueprintImplementableEvent)
	void DotUpdated(const FVector2D& X_Min, const FVector2D& X_Max, const FVector2D& Y_Min, const FVector2D& Y_Max, const bool InProgress);
};
