// Fill out your copyright notice in the Description page of Project Settings.


#include "Road.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include <random>
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
 

// Sets default values
ARoad::ARoad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FString DefaultMeshAssetPath = TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Plane.Plane'");
	PlaneTile = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *DefaultMeshAssetPath));
	SetDefaultMesh(DefaultMeshAssetPath, PlaneTile);	
}

// Called when the game starts or when spawned
void ARoad::BeginPlay()
{
	Super::BeginPlay();
	
 
 
	GenerateSurface();
	FixCrossing();
	
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

void ARoad::GenerateSurface()
{	
	FVector CurrentPosition;

	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			CurrentPosition = FVector(i * 500, j * 500, 0);
			UStaticMeshComponent* NewRoadComponent = NewObject<UStaticMeshComponent>(this);
			NewRoadComponent->SetStaticMesh(PlaneTile);
			 
			NewRoadComponent->SetRelativeLocation(CurrentPosition);
			
			NewRoadComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
			NewRoadComponent->SetWorldScale3D(FVector(5, 5, 1));
			NewRoadComponent->RegisterComponent();
			Chunks[i][j] = NewRoadComponent;
			ChunksState[i][j] = 0;
			NewRoadComponent->SetMaterial(0, GetPlaneMaterial(ChunksState[i][j]));
			//DrawDebugLine(GetWorld(), FVector(i * 1000 + 500, j * 1000 + 500, 0), FVector(i * 1000 + 500, j * 1000 + 500, 2000), FColor::Red, true, 100);
			
		}
	}
	GenerateRoads();
}
 
void ARoad::GenerateRoads()
{
	int X1 = 0, X2;
	int Y1 = 0, Y2;
	for (int i = 0; i <= 8; i ++)
	{
		X1 = 2 + rand() % 3, X2 = Size - (rand() % 3) - 2;
		Y1 = Y1 + 2 + rand() % 3, Y2 = Y1;
		BuildLine(FVector2D(X1, Y1), FVector2D(X2, Y2));


		X1 += rand() % 3;
		if (X1 > 15) break;
	}
	X1 = 0, X2;
	Y1 = 0, Y2;
	for (int i = 0; i <= 8; i++)
	{
		Y1 = 2 + rand() % 3, Y2 = Size - (rand() % 3) - 2;
		X1 = X1 + 2 + rand() % 3, X2 = X1;
		BuildLine(FVector2D(X1, Y1), FVector2D(X2, Y2));

		Y1 += rand() % 3;
		if (Y1 > 15) break;
	}
}

void ARoad::BuildLine(FVector2D FirstPoint, FVector2D SecondPoint)
{
	int X1 = FirstPoint.X;
	int	X2 = SecondPoint.X;
	int	Y1 = FirstPoint.Y;
	int	Y2 = SecondPoint.Y;

	FVector2D Direction;
	FVector2D Position = FirstPoint;
	bool RightDirection = true;

	

	if (FirstPoint.X == SecondPoint.X) {
		RightDirection = true;
		Direction = FVector2D(0, 1);
	}
	else if (FirstPoint.Y == SecondPoint.Y) {
		RightDirection = false;
		Direction = FVector2D(1, 0);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not a staight line"));
		return;
	}
		

	if (ChunksState[X1][Y1] == 0) {
		Chunks[X1][Y1]->SetMaterial(0, road_end);
		ChunksState[X1][Y1] = 1;
	}
	else {
		Chunks[X1][Y1]->SetMaterial(0, road_crossing);
		ChunksState[X1][Y1] = 4;
	}
	Chunks[X1][Y1]->SetWorldRotation(FRotator::MakeFromEuler(FVector(0.0f, 0.0f, Direction.Y) * FVector(0, 0, 90) + FVector(0, 0, -90)));
	FVector ResultVector = FVector(FirstPoint.X, FirstPoint.Y, 0) - FVector(SecondPoint.X, SecondPoint.Y, 0);
	for (int i = 1; i < ResultVector.Size(); i++)
	{
		X1 = Direction.X * i + Position.X;
		Y1 = Direction.Y * i + Position.Y;
		UE_LOG(LogTemp, Error, TEXT("ChunkState[%d][%d]: %d"), X1, Y1 + i, ChunksState[X1][Y1 + i]);

		if (ChunksState[X1][Y1] == 0)
		{
			Chunks[X1][Y1]->SetMaterial(0, road_straight);
			ChunksState[X1][Y1] = 2;
			
		}
		else
		{
			Chunks[X1][Y1]->SetMaterial(0, road_crossing);
			ChunksState[X1][Y1] = 4;
		}
		Chunks[X1][Y1]->SetWorldRotation(FRotator::MakeFromEuler(FVector(0.0f, 0.0f, Direction.Y) * FVector(0, 0, -90) + FVector(0, 0, -90)));
	}

	

	if (ChunksState[X2][Y2] == 0) {
		Chunks[X2][Y2]->SetMaterial(0, road_end);
		Chunks[X2][Y2]->SetWorldRotation(FRotator::MakeFromEuler(FVector(0.0f, 0.0f, Direction.Y) * FVector(0, 0, 90) + FVector(0, 0, 90)));
		ChunksState[X2][Y2] = 1;
	}
	else {
		Chunks[X2][Y2]->SetMaterial(0, road_crossing);
		ChunksState[X2][Y2] = 4;
		Chunks[X2][Y2]->SetWorldRotation(FRotator::MakeFromEuler(FVector(0.0f, 0.0f, Direction.Y) * FVector(0, 0, 90) + FVector(0, 0, 90)));
	}
}

UMaterialInterface* ARoad::GetPlaneMaterial(int id_material)
{
	if (id_material == 0) return grass;
	if (id_material == 1) return road_end;
	if (id_material == 2) return road_turn;
	if (id_material == 3) return road_left_right;
	if (id_material == 4) return road_crossing;
	if (id_material == 5) return road_straight;
	
	return ERROR_MATERIAL;
}

void ARoad::FixCrossing()
{
	int RoadConnections;
	float AccumulatedRotation;
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			if (ChunksState[i][j] == 4)
			{
				
				RoadConnections = 0;
				AccumulatedRotation = Chunks[i][j]->GetComponentToWorld().GetRotation().X;
				UE_LOG(LogTemp, Warning, TEXT("RoadConections at (%d, %d)"), i, j);
				for (int SideNum = 0; SideNum < 4; SideNum++)
				{
					switch (SideNum)
					{
					case 0:
						if (i > 0 && ChunksState[i - 1][j] == 0)
						{
							UE_LOG(LogTemp, Warning, TEXT("RoadConection number %d"), RoadConnections);
						}
						else
						{
							RoadConnections += 1;
							UE_LOG(LogTemp, Warning, TEXT("RoadConection number %d"), RoadConnections);
						}
						break;
					case 1:
						if (j > 0 && ChunksState[i][j - 1] == 0)
						{
							UE_LOG(LogTemp, Warning, TEXT("RoadConection number %d"), RoadConnections);
							AccumulatedRotation -= 90;
						}
						else
						{
							RoadConnections += 1;
							UE_LOG(LogTemp, Warning, TEXT("RoadConection number %d"), RoadConnections);
						}
						break;
					case 2:
						if (i < 20 && ChunksState[i + 1][j] == 0)
						{
							UE_LOG(LogTemp, Warning, TEXT("RoadConection number %d"), RoadConnections);
							AccumulatedRotation -= 90;
						}
						else
						{
							RoadConnections += 1;
							UE_LOG(LogTemp, Warning, TEXT("RoadConection number %d"), RoadConnections);

						}
						break;
					case 3:
						if (j < 20 && ChunksState[i][j + 1] == 0)
						{
							UE_LOG(LogTemp, Warning, TEXT("RoadConection number %d"), RoadConnections);
							AccumulatedRotation -= 90;
						}
						else
						{
							RoadConnections += 1;
							UE_LOG(LogTemp, Warning, TEXT("RoadConection number %d"), RoadConnections);
						}
						break;
					default:
						UE_LOG(LogTemp, Warning, TEXT("Error. FixCrossing function sucks"),);
						break;
					}
				}
				
				UE_LOG(LogTemp, Warning, TEXT("RoadConection number %d"), RoadConnections);
				ChunksState[i][j] = RoadConnections;
				Chunks[i][j]->SetWorldRotation(FRotator(0.0f, AccumulatedRotation, 0.0f));
				Chunks[i][j]->SetMaterial(0, GetPlaneMaterial(ChunksState[i][j]));
			}
		}
	}
}