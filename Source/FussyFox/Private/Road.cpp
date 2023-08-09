// Fill out your copyright notice in the Description page of Project Settings.


#include "Road.h"
 
 
#include <random>
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
 

// Sets default values
ARoad::ARoad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FString DefaultMeshAssetPath = TEXT("/Script/Engine.StaticMesh'/Game/Assets/LevelGeneration/Meshes/PaneTile.PaneTile'");
	PaneTile = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *DefaultMeshAssetPath));
	SetDefaultMesh(DefaultMeshAssetPath, PaneTile);
 
}

// Called when the game starts or when spawned
void ARoad::BeginPlay()
{
	Super::BeginPlay();
	
 
 
	GenerateRoad(FVector(0,0,0), 10, FVector(1, 0 , 0));
 
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
 
 

int ARoad::getRandomNumber() {
	int RandomNum = rand() % 100;

	if (RandomNum <= 50) return 0;
	if (RandomNum >= 50 && RandomNum < 65) return 1;
	if (RandomNum >= 65 && RandomNum < 80) return 2;
	if (RandomNum >= 80 && RandomNum < 89) return 3;
	if (RandomNum >= 89 && RandomNum < 99) return 4;
	return 5;
}

void ARoad::GenerateRoad(FVector Roadposition, double GenerationStage, FVector RoadDirection)
{	
	double rotated = 1;
	FVector CurrentPosition;
	int randomNum = 0;
	float iteration = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			CurrentPosition = FVector(i * 1000, j * 1000, 0);
			UStaticMeshComponent* NewRoadComponent = NewObject<UStaticMeshComponent>(this);
			NewRoadComponent->SetStaticMesh(PaneTile);
			 
			NewRoadComponent->SetRelativeLocation(CurrentPosition);
			UE_LOG(LogTemp, Warning, TEXT("Pane created X: %f, Y: %f, Z: %f"), CurrentPosition.X, CurrentPosition.Y, CurrentPosition.Z);
			NewRoadComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
			NewRoadComponent->RegisterComponent();
			Chunks[i][j] = NewRoadComponent;
		}

	}
	
}
 
