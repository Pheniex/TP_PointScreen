// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotateActor.generated.h"

DECLARE_MULTICAST_DELEGATE_FiveParams(FOnDotChanged, const FVector2D, const FVector2D, const FVector2D, const FVector2D, const bool);

UCLASS()
class TP_POINTSCREEN_API ARotateActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	
	// Sets default values for this actor's properties
	ARotateActor();

	FOnDotChanged OnDotChanged;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SkeletalMesh")
	USkeletalMeshComponent* SMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", Meta = (ClampMin = 0.5, ClampMax = 5.f))
	float RotateDelay = 1.f;

	UFUNCTION(BlueprintCallable, Category = "SkeletalMesh")
	static bool GetSkeletalMeshVertexLocations(USkeletalMeshComponent* Mesh, TArray<FVector3f>& Locations, int32 LODIndex);

	UFUNCTION(BlueprintCallable, Category = "SkeletalMesh")
	static void SetCPUSkinningEnabled(USkinnedMeshComponent* Mesh, bool bEnable, bool bRecreateRenderStateImmediately);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void StartRotate();

	TArray<FVector3f> Locations;
	bool InProgress;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle RotateTimerHandle;
	void OnRotateMesh();

	TArray<FVector> SMeshVert;
};
