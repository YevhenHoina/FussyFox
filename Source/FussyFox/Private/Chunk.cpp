// Fill out your copyright notice in the Description page of Project Settings.


#include "Chunk.h"


AChunk::AChunk()
{
	FString MaterialAssetPath = TEXT("/Script/Engine.Material'/Game/Assets/LevelGeneration/Materials/M_Grass.M_Grass'");
	grass = LoadObject<UMaterialInterface>(nullptr, *MaterialAssetPath);

	MaterialAssetPath = TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Assets/LevelGeneration/Materials/RoadsInstances/MI_Road_End.MI_Road_End'");
	road_end = LoadObject<UMaterialInterface>(nullptr, *MaterialAssetPath);

	MaterialAssetPath = TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Assets/LevelGeneration/Materials/RoadsInstances/MI_Road_TurnRight.MI_Road_TurnRight'");
	road_turn = LoadObject<UMaterialInterface>(nullptr, *MaterialAssetPath);

	MaterialAssetPath = TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Assets/LevelGeneration/Materials/RoadsInstances/MI_Road_T_Crossing.MI_Road_T_Crossing'");
	road_left_right = LoadObject<UMaterialInterface>(nullptr, *MaterialAssetPath);

	MaterialAssetPath = TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Assets/LevelGeneration/Materials/RoadsInstances/MI_Road_X_Crossing.MI_Road_X_Crossing'");
	road_crossing = LoadObject<UMaterialInterface>(nullptr, *MaterialAssetPath);

	MaterialAssetPath = TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Assets/LevelGeneration/Materials/RoadsInstances/MI_Road_Straigh.MI_Road_Straigh'");
	road_straight = LoadObject<UMaterialInterface>(nullptr, *MaterialAssetPath);

	MaterialAssetPath = TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Assets/LevelPrototyping/Materials/ErrorMaterial.ErrorMaterial'");
	ERROR_MATERIAL = LoadObject<UMaterialInterface>(nullptr, *MaterialAssetPath);

	FString DefaultMeshAssetPath = TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Plane.Plane'");
	PlaneTile = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *DefaultMeshAssetPath));
	GetStaticMeshComponent()->SetStaticMesh(PlaneTile);
	GetStaticMeshComponent()->SetWorldScale3D(FVector::OneVector * 5.f);
	GetStaticMeshComponent()->SetMaterial(0, grass);
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
}

void AChunk::BeginPlay()
{
	
}

UMaterialInterface* AChunk::GetPlaneMaterial(int id_material)
{
	if (id_material == 0) return grass;
	if (id_material == 1) return road_end;
	if (id_material == 2) return road_turn;
	if (id_material == 3) return road_left_right;
	if (id_material == 4) return road_crossing;
	if (id_material == 5) return road_straight;

	return ERROR_MATERIAL;
}

