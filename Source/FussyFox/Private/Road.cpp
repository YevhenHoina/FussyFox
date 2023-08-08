// Fill out your copyright notice in the Description page of Project Settings.


#include "Road.h"

// Sets default values
ARoad::ARoad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FString DefaultMeshAssetPath = TEXT("/Game/Content/Assets/LevelGeneration/");
	UStaticMesh* DefaultMeshAsset = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *DefaultMeshAssetPath));

	if (!DefaultMeshAsset)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load the default mesh asset: %s"), *DefaultMeshAssetPath);
	}
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

