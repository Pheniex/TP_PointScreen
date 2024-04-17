// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "RotateActor.h"

#include "Kismet/GameplayStatics.h"



void UMainWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	TArray<AActor*> RotateActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARotateActor::StaticClass(), RotateActors);
	for (auto it : RotateActors)
	{
		RotateActor = Cast<ARotateActor>(it);
	}

	RotateActor->OnDotChanged.AddUObject(this, &ThisClass::OnDotReceived);
}

void UMainWidget::OnDotReceived(const FVector2D XMin, const FVector2D XMax, const FVector2D YMin, const FVector2D YMax, const bool InProg)
{
	DotUpdated(XMin, XMax, YMin, YMax, InProg);
}
