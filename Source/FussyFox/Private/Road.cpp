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
	
	
	//testFunction();
	GenerateSurface();
	GenerateRoads();
}

// Called every frame
void ARoad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	
	UWorld* World = GetWorld();

	//Generate surface of grass only
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
}
 
void ARoad::BuildLine(FVector2D FirstPoint, FVector2D SecondPoint)
{
	int X1 = FirstPoint.X;
	int Y1 = FirstPoint.Y;
	int X2 = SecondPoint.X;
	int Y2 = SecondPoint.Y;
	FVector2D Direction;
	if (FirstPoint.X == SecondPoint.X)
	{
		Direction = FVector2D(0, 1);
	}
	else if (FirstPoint.Y == SecondPoint.Y)
	{
		Direction = FVector2D(1, 0);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("The line is no straight"));
		return;
	}


	Chunks[X1][Y1]->GetStaticMeshComponent()->SetMaterial(0, Chunks[X1][Y1]->GetPlaneMaterial(1));
	Chunks[X1][Y1]->GetStaticMeshComponent()->SetWorldRotation(FRotator(0, -90 * Direction.X + 180, 0));
	Chunks[X1][Y1]->ID_MATERIAL = 1;
	FVector ResultVector = FVector(FirstPoint.X, FirstPoint.Y, 0) - FVector(SecondPoint.X, SecondPoint.Y, 0);
	for (int i = 0; i < ResultVector.Size2D() - 1; i++)
	{
		X1 = i * Direction.X + Direction.X + FirstPoint.X;
		Y1 = i * Direction.Y + Direction.Y + FirstPoint.Y;


		if ((Chunks[X1][Y1]->ID_MATERIAL) == 0)
		{
			Chunks[X1][Y1]->GetStaticMeshComponent()->SetMaterial(0, Chunks[X1][Y1]->GetPlaneMaterial(5));
			Chunks[X1][Y1]->GetStaticMeshComponent()->SetWorldRotation(FRotator(0, 90 * Direction.X, 0));
			Chunks[X1][Y1]->ID_MATERIAL = 5;
		}
		else
		{
			Chunks[X1][Y1]->GetStaticMeshComponent()->SetMaterial(0, Chunks[X1][Y1]->GetPlaneMaterial(4));
			Chunks[X1][Y1]->GetStaticMeshComponent()->SetWorldRotation(FRotator(0, 90 * Direction.X, 0));
			Chunks[X1][Y1]->ID_MATERIAL = 4;
		}
	}
	Chunks[X2][Y2]->GetStaticMeshComponent()->SetMaterial(0, Chunks[X1][Y1]->GetPlaneMaterial(1));
	Chunks[X2][Y2]->GetStaticMeshComponent()->SetWorldRotation(FRotator(0, -90 * Direction.X, 0));
	Chunks[X2][Y2]->ID_MATERIAL = 1;
}

void ARoad::GenerateRoads()
{
	int X1 = 0, X2;
	int Y1 = 0, Y2;
	for (int i = 0; i <= 15; i++)
	{
		X1 = 2 + rand() % 6, X2 = Size - (rand() % 6) - 2;
		Y1 = Y1 + 2 + rand() % 3, Y2 = Y1;
		BuildLine(FVector2D(X1, Y1), FVector2D(X2, Y2));


		X1 += rand() % 3;
		if (X1 > 15) break;
	}
	X1 = 0, X2;
	Y1 = 0, Y2;
	for (int i = 0; i <= 15; i++)
	{
		Y1 = 2 + rand() % 6, Y2 = Size - (rand() % 6) - 2;
		X1 = X1 + 2 + rand() % 3, X2 = X1;
		BuildLine(FVector2D(X1, Y1), FVector2D(X2, Y2));

		Y1 += rand() % 3;
		if (Y1 > 15) break;
	}
}