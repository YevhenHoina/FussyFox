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
	

	/*
	//UPROPERTY(EditAnywhere, Meta = (TEXT("Straight prospect road")))
	UPROPERTY(EditAnyWhere)
	UStaticMeshComponent* prospect_straight;

	//UPROPERTY(EditAnywhere, Meta = (TEXT("Turn tight prospect road")))
	UPROPERTY(EditAnyWhere)
	UStaticMeshComponent* prospect_right;

	//UPROPERTY(EditAnywhere, Meta = (TEXT("Trun left prospect road")))
	UPROPERTY(EditAnyWhere)
	UStaticMeshComponent* prospect_left;

	//UPROPERTY(EditAnywhere, Meta = (TEXT("T-crossing prospect road")))
	UPROPERTY(EditAnyWhere)
	UStaticMeshComponent* prospect_left_right;

	//UPROPERTY(EditAnywhere, Meta = (TEXT("X-crossing prospect road")))
	UPROPERTY(EditAnyWhere)
	UStaticMeshComponent* prospect_crossing;*/



	//UPROPERTY(EditAnywhere, Meta = (TEXT("Straight prospect road")))
	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMesh* PaneTile;	

	UStaticMesh* Prospects[6];
	UStaticMeshComponent* Chunks[10][10];
	void SetDefaultMesh(FString AssetPath, UStaticMesh* MeshToCheck);
	int getRandomNumber();
	void GenerateRoad(FVector Roadposition, double GenerationStage, FVector RoadDirection);



};
