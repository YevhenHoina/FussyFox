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

	FString DefaultMeshAssetPath = TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Plane.Plane'");
	PaneTile = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *DefaultMeshAssetPath));
	SetDefaultMesh(DefaultMeshAssetPath, PaneTile);
 
	
}

// Called when the game starts or when spawned
void ARoad::BeginPlay()
{
	Super::BeginPlay();
	
 
 
	GenerateSurface(FVector(0,0,0), 10, FVector(1, 0 , 0));
	BuildLine(FVector2D(3, 1), FVector2D(3, 10));
	BuildLine(FVector2D(5, 1), FVector2D(5, 10));
	BuildLine(FVector2D(3, 4), FVector2D(13, 4));
 
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

void ARoad::GenerateSurface(FVector Roadposition, double GenerationStage, FVector RoadDirection)
{	
	FVector CurrentPosition;

	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			CurrentPosition = FVector(i * 1000, j * 1000, 0);
			UStaticMeshComponent* NewRoadComponent = NewObject<UStaticMeshComponent>(this);
			NewRoadComponent->SetStaticMesh(PaneTile);
			 
			NewRoadComponent->SetRelativeLocation(CurrentPosition);
			
			NewRoadComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
			NewRoadComponent->SetWorldScale3D(FVector(10, 10, 1));
			NewRoadComponent->RegisterComponent();
			Chunks[i][j] = NewRoadComponent;
			DrawDebugLine(GetWorld(), FVector(i * 1000 + 500, j * 1000 + 500, 0), FVector(i * 1000 + 500, j * 1000 + 500, 2000), FColor::Red, true, 100);
			
		}
	}
	GenerateRoads();
}
 
void ARoad::GenerateRoads()
{
	
	BuildLine(FVector2D(3, 1), FVector2D(3, 10));
	BuildLine(FVector2D(5, 1), FVector2D(5, 10));
	BuildLine(FVector2D(3, 4), FVector2D(13, 4));
	
}

void ARoad::BuildLine(FVector2D FirstPoint, FVector2D SecondPoint)
{
	int X1 = FirstPoint.X;
	int	X2 = SecondPoint.X;
	int	Y1 = FirstPoint.Y;
	int	Y2 = SecondPoint.Y;

	if (X1 == X2)
	{
		
		Chunks[X1][Y1]->SetMaterial(0, road_end);
		for (int i = 1; i < Y2; i++)
		{
			if (true) // (Chunks[X1][Y1 + i]->GetMaterial(0)->GetName() != "MI_Road_Straigh") //doesn't work
			{
				Chunks[X1][Y1 + i]->SetMaterial(0, road_straight);
			}
			else Chunks[X1][Y1 + i]->SetMaterial(0, road_crossing);
		}
		Chunks[X2][Y2]->SetMaterial(0, road_end);
		Chunks[X2][Y2]->SetWorldRotation(FRotator(0, -180, 0));
	}
	else if (Y1 == Y2)
	{
		Chunks[X1][Y1]->SetMaterial(0, road_end);
		Chunks[X1][Y1]->SetWorldRotation(FRotator(0, -90, 0));
		for (int i = 1; i < X2 - 3; i++)
		{
			if (true) // (Chunks[X1 + i][Y1]->GetMaterial(0)->GetName() != "MI_Road_Straigh") //doesn't work
			{
				Chunks[X1 + i][Y1]->SetMaterial(0, road_straight);
				Chunks[X1 + i][Y1]->SetWorldRotation(FRotator(0, 90, 0));
			}
			else Chunks[X1 + i][Y1]->SetMaterial(0, road_crossing);
			
		}
		Chunks[X2][Y2]->SetMaterial(0, road_end);
		Chunks[X2][Y2]->SetWorldRotation(FRotator(0, 90, 0));
	}
	else UE_LOG(LogTemp, Warning, TEXT("Not a staight line"));


}