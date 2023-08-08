// Fill out your copyright notice in the Description page of Project Settings.


#include "Road.h"
<<<<<<< HEAD
=======
#include <random>
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
>>>>>>> main

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
<<<<<<< HEAD
	
=======

	Prospects[0] = prospect_straight;
	Prospects[1] = prospect_right;
	Prospects[2] = prospect_left;
	Prospects[3] = prospect_left_right;
	Prospects[4] = prospect_crossing;
	Prospects[5] = prospect_end;


	InitialMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Start crossing"));
	InitialMeshComponent->SetupAttachment(RootComponent);

>>>>>>> main
}

// Called when the game starts or when spawned
void ARoad::BeginPlay()
{
	Super::BeginPlay();
	
<<<<<<< HEAD
=======
	GenerateRoad(FVector(0,0,0), 20, FVector(1, 0 , 0));
>>>>>>> main
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
<<<<<<< HEAD
=======

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
	for (double i = 0; i <= GenerationStage; i ++)
	{

		CurrentPosition = (1000 * i) * RoadDirection + Roadposition;
		UStaticMeshComponent* NewRoadComponent = NewObject<UStaticMeshComponent>(this);
		NewRoadComponent->SetStaticMesh(Prospects[getRandomNumber()]);
		NewRoadComponent->SetRelativeLocation(CurrentPosition);
		UE_LOG(LogTemp, Warning, TEXT("Pane created X: %f, Y: %f, Z: %f"), CurrentPosition.X, CurrentPosition.Y, CurrentPosition.Z);
		NewRoadComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		NewRoadComponent->RegisterComponent();

		if (randomNum == 0) randomNum = getRandomNumber();

		if ((randomNum == 1) || (randomNum == 4)) {
			GenerateRoad(
				(1000 * i) * RoadDirection + Roadposition,
				GenerationStage - 1,
				FVector(0, 1, 0) * rotated
				);
			randomNum = 0;
			rotated *= -1;
		}

		if ((randomNum == 2) || (randomNum == 4)) {
			GenerateRoad(
				(1000 * i) * RoadDirection + Roadposition,
				GenerationStage - 1,
				FVector(0, -1, 0) * rotated
			);
			randomNum = 0;
			rotated *= -1;
		}

		if (randomNum == 3) {
			GenerateRoad(
				(1000 * i) * RoadDirection + Roadposition,
				GenerationStage - 1,
				FVector(0, -1, 0) * rotated
			);
			GenerateRoad(
				(1000 * i) * RoadDirection + Roadposition,
				GenerationStage - 1,
				FVector(0, 1, 0) * rotated
			);
			GenerationStage = 0;
			randomNum = 0;
			rotated *= -1;
		}
		if (randomNum == 5) GenerationStage = 0;
		
		GenerationStage--;
	}
	
}
>>>>>>> main
