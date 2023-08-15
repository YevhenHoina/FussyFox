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
}
 
