// Fill out your copyright notice in the Description page of Project Settings.


#include "RotateActor.h"
#include "SkeletalRenderPublic.h"
#include "Rendering/SkeletalMeshRenderData.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Vector2D.h"

// Sets default values
ARotateActor::ARotateActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SMesh->AttachToComponent(ThisClass::GetDefaultAttachComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ARotateActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARotateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARotateActor::OnRotateMesh()
{
	SMesh->SetRelativeRotation(SMesh->GetRelativeRotation() + FRotator(0,10,0));

	UE_LOG(LogTemp, Warning, TEXT("Rotation: %s"), *SMesh->GetRelativeRotation().ToString());
	
	GetSkeletalMeshVertexLocations(SMesh, Locations, 0);
	
	auto Controller = GetWorld()->GetFirstPlayerController();
	FVector2D Position, X_Min(50000, 0), X_Max(0, 0), Y_Min(0, 50000), Y_Max(0, 0);

	for (FVector3f it : Locations)
	{
		UGameplayStatics::ProjectWorldToScreen(Controller, FVector(it), Position);
		if (Position.X < X_Min.X)
		{
			X_Min = Position;
		}
		if (Position.X > X_Max.X)
		{
			X_Max = Position;
		}
		if (Position.Y < Y_Min.Y)
		{
			Y_Min = Position;
		}
		if (Position.Y > Y_Max.Y) 
		{
			Y_Max = Position;
		}
	}
	
	if (SMesh->GetRelativeRotation().Equals(FRotator(0.f, 0.f, 0.f), 1.f))
	{
		GetWorldTimerManager().ClearTimer(RotateTimerHandle);
		InProgress = false;
	}
	
	OnDotChanged.Broadcast(X_Min, X_Max, Y_Min, Y_Max, InProgress);
}

bool ARotateActor::GetSkeletalMeshVertexLocations(USkeletalMeshComponent* Mesh, TArray<FVector3f>& Locations, int32 LODIndex)
{
	if (!Mesh || !Mesh->SkeletalMesh) return false;

	//CPU or GPU skinning
	if (Mesh->GetCPUSkinningEnabled()) {
		TArray<FFinalSkinVertex> SkinnedVertices;
		Mesh->GetCPUSkinnedVertices(SkinnedVertices, LODIndex);
		Locations.Empty();
		Locations.AddUninitialized(SkinnedVertices.Num());
		for (int32 i = 0; i < SkinnedVertices.Num(); ++i) {
			Locations[i] = SkinnedVertices[i].Position;
		}
	}
	else {
		const FSkeletalMeshRenderData* RenderData = Mesh->GetSkeletalMeshRenderData();
		if (!RenderData) return false;
		const FSkeletalMeshLODRenderData& LOD = RenderData->LODRenderData[LODIndex];
		const FSkinWeightVertexBuffer& Buffer = LOD.SkinWeightVertexBuffer;
		TArray<FMatrix44f> CacheToLocals;
		Mesh->GetCurrentRefToLocalMatrices(CacheToLocals, LODIndex);
		Mesh->ComputeSkinnedPositions(Mesh, Locations, CacheToLocals, LOD, Buffer);
	}

	//LocalToWorld
	const FTransform ToWorld = Mesh->GetComponentTransform();
	for (FVector3f& EachVertex : Locations) {
		EachVertex = FVector3f(ToWorld.TransformPosition(FVector(EachVertex)));
	}

	return true;
}

void ARotateActor::SetCPUSkinningEnabled(USkinnedMeshComponent* Mesh, bool bEnable, bool bRecreateRenderStateImmediately)
{
	Mesh->SetCPUSkinningEnabled(bEnable, bRecreateRenderStateImmediately);
}

void ARotateActor::StartRotate()
{
	InProgress = true;
	GetWorldTimerManager().SetTimer(RotateTimerHandle, this, &ThisClass::OnRotateMesh, RotateDelay, true);
}
