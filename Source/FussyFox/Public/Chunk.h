// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Chunk.generated.h"

/**
 *
 */
UCLASS()
class FUSSYFOX_API AChunk : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AChunk();

	virtual void BeginPlay() override;

	int32 ID_MATERIAL = 0;

	UPROPERTY(EditAnyWhere, Category = "Roads")
		UMaterialInterface* grass;

	UPROPERTY(EditAnyWhere, Category = "Roads")
		UMaterialInterface* road_end;

	UPROPERTY(EditAnyWhere, Category = "Roads")
		UMaterialInterface* road_turn;

	UPROPERTY(EditAnyWhere, Category = "Roads")
		UMaterialInterface* road_left_right;

	UPROPERTY(EditAnyWhere, Category = "Roads")
		UMaterialInterface* road_crossing;

	UPROPERTY(EditAnyWhere, Category = "Roads")
		UMaterialInterface* road_straight;



	UPROPERTY(EditAnyWhere, Category = "Roads")
		UMaterialInterface* ERROR_MATERIAL;

	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMesh* PlaneTile;

	UMaterialInterface* GetPlaneMaterial(int id_material);

public:

};
