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

	Prospects[0] = prospect_straight;
	Prospects[1] = prospect_right;
	Prospects[2] = prospect_left;
	Prospects[3] = prospect_left_right;
	Prospects[4] = prospect_crossing;
	Prospects[5] = prospect_end;


	InitialMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Start crossing"));
	InitialMeshComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ARoad::BeginPlay()
{
	Super::BeginPlay();
	
	GenerateRoad(FVector(0,0,0), 4, FVector(1, 0 , 0));
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
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);

	double randNum = dis(gen);

	if (randNum <= 0.8)
		return 1;
	else if (randNum <= 0.9)
		return 2;
	else if (randNum <= 0.95)
		return 3;
	else if (randNum <= 0.99)
		return 4;
	else if (randNum <= 0.993)
		return 5;
	else
		return 6;
}

void ARoad::GenerateRoad(FVector Roadposition, double GenerationStage, FVector RoadDirection)
{
	int randomNum = 4;
	float iteration = 0;
	for (double i = 0; i <= GenerationStage; i ++)
	{
		UStaticMeshComponent* NewRoadComponent = NewObject<UStaticMeshComponent>(this);
		NewRoadComponent->SetStaticMesh(Prospects[randomNum]);
		NewRoadComponent->SetWorldLocation((1000 * i) * RoadDirection + Roadposition);
		NewRoadComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		NewRoadComponent->RegisterComponent();

		if ((randomNum == 1) || (randomNum == 4)) {
			GenerateRoad(
				(1000 * i) * RoadDirection + Roadposition,
				GenerationStage - 1,
				FVector(0, 1, 0)
				);
		}

		if ((randomNum == 2) || (randomNum == 4)) {
			GenerateRoad(
				(1000 * i) * RoadDirection + Roadposition,
				GenerationStage - 1,
				FVector(0, -1, 0)
			);
		}

		if (randomNum == 3) {
			GenerateRoad(
				(1000 * i) * RoadDirection + Roadposition,
				GenerationStage - 1,
				FVector(0, -1, 0)
			);
			GenerationStage = 0;
		}
	}
	
}
