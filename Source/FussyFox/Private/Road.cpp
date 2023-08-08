// Fill out your copyright notice in the Description page of Project Settings.


#include "Road.h"

// Sets default values
ARoad::ARoad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FString DefaultMeshAssetPath = TEXT("/Script/Engine.StaticMesh'/Game/Assets/LevelGeneration/prospect_crossing.prospect_straight'");
	prospect_straight = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *DefaultMeshAssetPath));
	MESH_NOT_FOUND_ERROR(DefaultMeshAssetPath, prospect_straight);

		DefaultMeshAssetPath = TEXT("/Script/Engine.StaticMesh'/Game/Assets/LevelGeneration/prospect_crossing.prospect_right'");
	prospect_right = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *DefaultMeshAssetPath));
	MESH_NOT_FOUND_ERROR(DefaultMeshAssetPath, prospect_right);

		DefaultMeshAssetPath = TEXT("/Script/Engine.StaticMesh'/Game/Assets/LevelGeneration/prospect_crossing.prospect_left'");
	prospect_left = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *DefaultMeshAssetPath));
	MESH_NOT_FOUND_ERROR(DefaultMeshAssetPath, prospect_left);

		DefaultMeshAssetPath = TEXT("/Script/Engine.StaticMesh'/Game/Assets/LevelGeneration/prospect_crossing.prospect_left_adn_right'");
	prospect_left_right = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *DefaultMeshAssetPath));
	MESH_NOT_FOUND_ERROR(DefaultMeshAssetPath, prospect_left_right);

		DefaultMeshAssetPath = TEXT("/Script/Engine.StaticMesh'/Game/Assets/LevelGeneration/prospect_crossing.prospect_crossing'");
	MESH_NOT_FOUND_ERROR(DefaultMeshAssetPath, prospect_crossing);

	
}

// Called when the game starts or when spawned
void ARoad::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ARoad::MESH_NOT_FOUND_ERROR(FString AssetPath, UStaticMesh* MeshToCheck)
{
	if (!MeshToCheck)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load the default mesh asset: %s"), *AssetPath);
	}
}
