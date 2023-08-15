// Fill out your copyright notice in the Description page of Project Settings.


#include "Road.h"
#include "Chunk.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include <random>
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
 

// Sets default values
ARoad::ARoad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void ARoad::BeginPlay()
{
	Super::BeginPlay();
	
	
 
	GenerateSurface();
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
	AChunk* Chunks[60][60];
	UWorld* World = GetWorld();

	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			

			if (World)
			{
				CurrentPosition = FVector(i * 500, j * 500, 0);
				// Spawn an instance of the AChunk actor class
				Chunks[i][j] = World->SpawnActor<AChunk>(AChunk::StaticClass(), CurrentPosition, FRotator::ZeroRotator);

				// Check if the actor was created successfully
				if (!Chunks[i][j])
				{
					UE_LOG(LogTemp, Warning, TEXT("Failed to spawn the Chunk actor."));
				}
			}
		}
	}
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			UE_LOG(LogTemp, Warning, TEXT("At cordinates (%d, %d) is %s"), i, j, *Chunks[i][j]->Name);
		}
	}
}
 
/*
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
		

	Chunks[X1][Y1]->SetMaterial(0, road_crossing);
	ChunksState[X1][Y1] = 4;
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

	

	
	Chunks[X2][Y2]->SetMaterial(0, road_crossing);
	ChunksState[X2][Y2] = 4;
	Chunks[X2][Y2]->SetWorldRotation(FRotator::MakeFromEuler(FVector(0.0f, 0.0f, Direction.Y) * FVector(0, 0, 90) + FVector(0, 0, 90)));
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
				ChunksState[i][j] = RoadConnections;
				switch (RoadConnections)
				{

				case 2:
					if (ChunksState[i - 1][j] && ChunksState[i + 1][j] ||
						ChunksState[i][j - 1] && ChunksState[i][j + 1])
						ChunksState[i][j] = 5;
					break;
				case 3:
					AccumulatedRotation = ((ChunksState[i][j - 1] == 0) || (ChunksState[i][j - 1] == 0)) ? AccumulatedRotation * (-1): AccumulatedRotation;
					break;
				default:
					break;
				}
				
				UE_LOG(LogTemp, Warning, TEXT("RoadConection number %d"), RoadConnections);
				
				Chunks[i][j]->SetWorldRotation(FRotator(0.0f, AccumulatedRotation, 0.0f));
				Chunks[i][j]->SetMaterial(0, GetPlaneMaterial(ChunksState[i][j]));
			}
		}
	}
}
*/