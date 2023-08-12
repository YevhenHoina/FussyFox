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
	
	UPROPERTY(EditAnywhere, Category = "Generation")
		int Size = 40;
	
	//UPROPERTY(EditAnywhere, Meta = (TEXT("Straight road")))
	UPROPERTY(EditAnyWhere, Category="Roads")
		UMaterialInterface* road_straight;

	//UPROPERTY(EditAnywhere, Meta = (TEXT("Turn tight road")))
	UPROPERTY(EditAnyWhere, Category = "Roads")
		UMaterialInterface* road_right;

	//UPROPERTY(EditAnywhere, Meta = (TEXT("Trun left road")))
	UPROPERTY(EditAnyWhere, Category = "Roads")
		UMaterialInterface* road_turn;

	//UPROPERTY(EditAnywhere, Meta = (TEXT("T-crossing road")))
	UPROPERTY(EditAnyWhere, Category = "Roads")
		UMaterialInterface* road_left_right;

	//UPROPERTY(EditAnywhere, Meta = (TEXT("X-crossing road")))
	UPROPERTY(EditAnyWhere, Category = "Roads")
		UMaterialInterface* road_crossing;

	UPROPERTY(EditAnyWhere, Category = "Roads")
		UMaterialInterface* road_end;

	UPROPERTY(EditAnyWhere, Category = "Roads")
		UMaterialInterface* grass;

	UPROPERTY(EditAnyWhere, Category = "Roads")
		UMaterialInterface* ERROR_MATERIAL;

	//UPROPERTY(EditAnywhere, Meta = (TEXT("Straight road")))
	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMesh* PlaneTile;



	UStaticMeshComponent* Chunks[40][40];
	int ChunksState[40][40];

private:
	void SetDefaultMesh(FString AssetPath, UStaticMesh* MeshToCheck);
	int getRandomNumber();
	void GenerateSurface();
	void GenerateRoads();
	void BuildLine(FVector2D FirstPoint, FVector2D SecondPoint);
	UMaterialInterface* SetCrossing(int X, int Y, int StateWillingToPlacee, FVector2D Direction);
	UMaterialInterface* GetPlaneMaterial(int id_material);
};
