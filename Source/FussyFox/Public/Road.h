// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Road.generated.h"

UCLASS()
class FUSSYFOX_API ARoad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

 
 
	UPROPERTY(EditAnyWhere)
		UStaticMeshComponent* InitialMeshComponent;
 
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

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


	int Size = 60;
	UStaticMeshComponent* Chunks[60][60];
	int ChunksState[60][60];

private:
	void SetDefaultMesh(FString AssetPath, UStaticMesh* MeshToCheck);
	int getRandomNumber();
	void GenerateSurface();
	void GenerateRoads();
	void BuildLine(FVector2D FirstPoint, FVector2D SecondPoint);
	void FixCrossing();
	UMaterialInterface* GetPlaneMaterial(int id_material);
};
