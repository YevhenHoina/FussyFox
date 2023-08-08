// Fill out your copyright notice in the Description page of Project Settings.


#include "Road.h"

// Sets default values
ARoad::ARoad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FString DefaultMeshAssetPath = TEXT("/Script/Engine.StaticMesh'/Game/Assets/LevelGeneration/prospect_straight.prospect_straight'");
	prospect_straight = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *DefaultMeshAssetPath));
	SetDefaultMesh(DefaultMeshAssetPath, prospect_straight);

		DefaultMeshAssetPath = TEXT("/Script/Engine.StaticMesh'/Game/Assets/LevelGeneration/prospect_right.prospect_right'");
	prospect_right = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *DefaultMeshAssetPath));
	SetDefaultMesh(DefaultMeshAssetPath, prospect_right);

		DefaultMeshAssetPath = TEXT("/Script/Engine.StaticMesh'/Game/Assets/LevelGeneration/prospect_left.prospect_left'");
	prospect_left = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *DefaultMeshAssetPath));
	SetDefaultMesh(DefaultMeshAssetPath, prospect_left);

		DefaultMeshAssetPath = TEXT("/Script/Engine.StaticMesh'/Game/Assets/LevelGeneration/prospect_left_and_right.prospect_left_and_right'");
	prospect_left_right = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *DefaultMeshAssetPath));
	SetDefaultMesh(DefaultMeshAssetPath, prospect_left_right);

		DefaultMeshAssetPath = TEXT("/Script/Engine.StaticMesh'/Game/Assets/LevelGeneration/prospect_crossing.prospect_crossing'");
	prospect_crossing = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *DefaultMeshAssetPath));
	SetDefaultMesh(DefaultMeshAssetPath, prospect_crossing);

	DefaultMeshAssetPath = TEXT("/Script/Engine.StaticMesh'/Game/Assets/LevelGeneration/prospect_end.prospect_end'");
	prospect_end = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *DefaultMeshAssetPath));
	SetDefaultMesh(DefaultMeshAssetPath, prospect_end);
	
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



void ARoad::SetDefaultMesh(FString AssetPath, UStaticMesh* MeshToCheck)
{
	

	MeshToCheck = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *AssetPath));

	if (!MeshToCheck)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load the default mesh asset: %s"), *AssetPath);
	}
}
