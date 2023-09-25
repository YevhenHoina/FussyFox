// Fill out your copyright notice in the Description page of Project Settings.


#include "Road.h"
#include "Chunk.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include <random>
#include "Engine/StaticMesh.h"
#include "DrawDebugHelpers.h"
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
	/*BuildLine(FVector2D(1, 5), FVector2D(1, 9));
	BuildLine(FVector2D(2, 4), FVector2D(5, 4));
	BuildLine(FVector2D(5, 5), FVector2D(5, 9));
	BuildLine(FVector2D(2, 17), FVector2D(15, 17));*/
	GenerateRoads();
	FixCrossing();
	test_building_generation();
	//TickTackFix();
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
				DrawDebugLine(GetWorld(), FVector(i * 500 + 250, j * 500 + 250, 0), FVector(i * 500 + 250, j * 500 + 250, 1000), FColor::Red, false, 1000, 0, 10);

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

	X1 += Direction.X;
	Y1 += Direction.Y;
	Chunks[X1][Y1]->GetStaticMeshComponent()->SetMaterial(0, Chunks[X1][Y1]->GetPlaneMaterial(4));
	Chunks[X1][Y1]->GetStaticMeshComponent()->SetWorldRotation(FRotator(0, -90 * Direction.X + 180, 0));
	Chunks[X1][Y1]->ID_MATERIAL = 4;
	FVector ResultVector = FVector(FirstPoint.X, FirstPoint.Y, 0) - FVector(SecondPoint.X, SecondPoint.Y, 0);
	for (int i = 1; i < ResultVector.Size2D() - 1; i++)
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
	Chunks[X1][Y1]->GetStaticMeshComponent()->SetMaterial(0, Chunks[X1][Y1]->GetPlaneMaterial(4));
	Chunks[X1][Y1]->GetStaticMeshComponent()->SetWorldRotation(FRotator(0, -90 * Direction.X, 0));
	Chunks[X1][Y1]->ID_MATERIAL = 4;
}

void ARoad::DestroyLine(FVector2D FirstPoint, FVector2D SecondPoint)
{
	int X1 = FirstPoint.X;
	int Y1 = FirstPoint.Y;
	int X2 = SecondPoint.X;
	int Y2 = SecondPoint.Y;

	int X, Y; //NearPoints

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

	FVector ResultVector = FVector(FirstPoint.X, FirstPoint.Y, 0) - FVector(SecondPoint.X, SecondPoint.Y, 0);
	for (int i = 0; i < ResultVector.Size2D() - 1; i++)
	{
		X1 = i * Direction.X + Direction.X + FirstPoint.X;
		Y1 = i * Direction.Y + Direction.Y + FirstPoint.Y;


		if ((Chunks[X1][Y1]->ID_MATERIAL) == 0)
		{
			Chunks[X1][Y1]->GetStaticMeshComponent()->SetMaterial(0, Chunks[X1][Y1]->GetPlaneMaterial(0));
			Chunks[X1][Y1]->GetStaticMeshComponent()->SetWorldRotation(FRotator(0, 90 * Direction.X, 0));
			Chunks[X1][Y1]->ID_MATERIAL = 0;
		}
		else
		{
			Chunks[X1][Y1]->GetStaticMeshComponent()->SetMaterial(0, Chunks[X1][Y1]->GetPlaneMaterial(0));
			Chunks[X1][Y1]->GetStaticMeshComponent()->SetWorldRotation(FRotator(0, 90 * Direction.X, 0));
			Chunks[X1][Y1]->ID_MATERIAL = 0;
		}
		X = X1 + Direction.Y;
		Y = Y1 + Direction.X; 
		if ((Chunks[X][Y])->ID_MATERIAL != 0)
		{
			Chunks[X][Y]->GetStaticMeshComponent()->SetMaterial(0, Chunks[X1][Y1]->GetPlaneMaterial(4));
			Chunks[X][Y]->GetStaticMeshComponent()->SetWorldRotation(FRotator(0, 90 * Direction.X, 0));
			Chunks[X][Y]->ID_MATERIAL = 4;
		}

		X = X1 - Direction.Y;
		Y = Y1 - Direction.X;
		if ((Chunks[X][Y])->ID_MATERIAL != 0)
		{
			Chunks[X][Y]->GetStaticMeshComponent()->SetMaterial(0, Chunks[X1][Y1]->GetPlaneMaterial(4));
			Chunks[X][Y]->GetStaticMeshComponent()->SetWorldRotation(FRotator(0, 90 * Direction.X, 0));
			Chunks[X][Y]->ID_MATERIAL = 4;
		}
	}
}


void ARoad::GenerateRoads()
{
	int X1 = 0, X2;
	int Y1 = 0, Y2;
	for (int i = 0; i <= 17; i++)
	{
		X1 = 2 + rand() % 8, X2 = Size - (rand() % 3) - 5;
		Y1 = Y1 + 3 + rand() % 3, Y2 = Y1;

		if (X1 > 58) break;
		if (Y1 > 50) break;
		if (X2 > 58) break;
		if (Y2 > 58) break;

		BuildLine(FVector2D(X1, Y1), FVector2D(X2, Y2));


		X1 += rand() % 3;
	}
	X1 = 0, X2;
	Y1 = 0, Y2;
	for (int i = 0; i <= 17; i++)
	{
		Y1 = 2 + rand() % 8, Y2 = Size - (rand() % 3) - 7;
		X1 = X1 + 3 + rand() % 3, X2 = X1;

		if (X1 > 50) break;
		if (Y1 > 58) break;
		if (X2 > 58) break;
		if (Y2 > 58) break;

		BuildLine(FVector2D(X1, Y1), FVector2D(X2, Y2));

		Y1 += rand() % 3;
	}

	for (int i = 0; i <= 4; i++)
	{
		for (int j = 0; j <= 4; j++)
		{
			X1 = 15 + 5 * i + (rand() % 10);
			X2 = X1 + (rand() % 5);
			Y1 = 20 * j + (rand() % 10);

			if (X1 > 58) break;
			if (Y1 > 50) break;
			if (X2 > 58) break;

			for (int k = 0; k <= 6; k++)
			{

				DestroyLine(FVector2D(X1, Y1 + k), FVector2D(X2, Y1 + k));
			}
			
		}
	}
	for (int i = 0; i <= 12; i++)
	{
		DestroyLine(FVector2D(0, i), FVector2D(12, i));
		(FVector2D(i, 48), FVector2D(i, 59));
		(FVector2D(i, 0), FVector2D(i, 16));
		//DestroyLine(FVector2D(37, Size - i), FVector2D(59, Size - i));
		DestroyLine(FVector2D(42, i), FVector2D(59, i));
	}
}

void ARoad::FixCrossing()
{
	int Connections = 0;

	//each byte represents a direction;
	float Rotation = 0;
	for (int i = 1; i < Size - 1; i++)
	{
		for (int j = 1; j < Size - 1; j++)
		{
			if (Chunks[i][j]->ID_MATERIAL != 0)
			{
				if (Chunks[i][j]->Pose == 0)
				{
					if (Chunks[i + 1][j]->ID_MATERIAL != 0) {
						Connections += 1;
						Chunks[i][j]->Pose += 0b1000;
					}
					if (Chunks[i][j + 1]->ID_MATERIAL != 0) {
						Connections += 1;
						Chunks[i][j]->Pose += 0b0100;
					}
					if (Chunks[i - 1][j]->ID_MATERIAL != 0) {
						Connections += 1;
						Chunks[i][j]->Pose += 0b0010;
					}
					if (Chunks[i][j - 1]->ID_MATERIAL != 0) {
						Connections += 1;
						Chunks[i][j]->Pose += 0b0001;
					}
				}
				
				if (Connections == 1)
				{
					for (int position = 0; position < sizeof(int) * 8; ++position) {
						if ((Chunks[i][j]->Pose & (1 << position)) != 0) {
							Rotation = position * (-90);
							break;
						}
					}
				}
				if (Connections == 2)
				{
					//If this is straight connections than do straight road, but not a turn
					if (((Chunks[i + 1][j]->ID_MATERIAL != 0) && (Chunks[i - 1][j]->ID_MATERIAL != 0))
						||
						((Chunks[i][j + 1]->ID_MATERIAL != 0) && (Chunks[i][j - 1]->ID_MATERIAL != 0)))
					{
						Connections = 5;
						Chunks[i][j]->GetStaticMeshComponent()->SetMaterial(0, (Chunks[i][j]->GetPlaneMaterial(Connections)));
						Chunks[i][j]->ID_MATERIAL = Connections;
						Connections = 0;
						Rotation = 0;
						continue;
					}
					else
					{

						//This is bad
						//I have no idea why thing is even working
						//As if-else solution it might be the best actualy
						if (Chunks[i][j]->Pose & 1)
						{
							Rotation = 90;
						}
						if (Chunks[i][j]->Pose >> 3 & 1)
						{
							Rotation -= 90;
							if (Chunks[i][j]->Pose & 1) Rotation = 180;
						}

					}


				}
				if (Connections == 3)
				{
					for (int position = 0; position < sizeof(int) * 8; ++position) {
						if ((Chunks[i][j]->Pose & (1 << position)) == 0) {
							Rotation = position * (-90);
							break;
						}
					}
				}

				Chunks[i][j]->GetStaticMeshComponent()->SetMaterial(0, (Chunks[i][j]->GetPlaneMaterial(Connections)));
				Chunks[i][j]->ID_MATERIAL = Connections;
				Chunks[i][j]->GetStaticMeshComponent()->SetWorldRotation(FRotator(0, Rotation, 0));
				Connections = 0;
				Rotation = 0;
			}
		}
	}
}

// this functions sucks
void ARoad::TickTackFix()
{
	FVector2D FirstPoint;
	FVector2D SecondPoint;
	int counter = 0;
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			if (counter == 1 && Chunks[i][j]->ID_MATERIAL == 1)
			{
				UE_LOG(LogTemp, Warning, TEXT("Point number %d found in (%d, %d)"), counter, i, j);
				SecondPoint = FVector2D(i, j + 1);
				DestroyLine(FirstPoint, SecondPoint);
				UE_LOG(LogTemp, Warning, TEXT("Line destroyed from (%f, %f) to (%f, %f)"), counter, i, j);
			}
			/*if ((Chunks[i][j]->ID_MATERIAL == 2) || (Chunks[i][j]->ID_MATERIAL == 3) || (Chunks[i][j]->ID_MATERIAL == 4) || (Chunks[i][j]->ID_MATERIAL == 0))
				counter = 0;*/

			if (Chunks[i][j]->ID_MATERIAL == 1) {
				counter++;
				UE_LOG(LogTemp, Warning, TEXT("Point number %d found in (%d, %d)"), counter, i, j);
				FirstPoint = FVector2D(i, j - 1);
			}
			
		}
		counter = 0;
	}
	FixCrossing();
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			if (counter == 1 && Chunks[i][j]->ID_MATERIAL == 1)
			{
				UE_LOG(LogTemp, Warning, TEXT("Point number %d found in (%d, %d)"), counter, j, i);
				SecondPoint = FVector2D(j - 1, i + 1);
				DestroyLine(FirstPoint, SecondPoint);
				UE_LOG(LogTemp, Warning, TEXT("Line destroyed from (%f, %f) to (%f, %f)"), counter, j, i);
			}
			/*if ((Chunks[j][i]->ID_MATERIAL == 2) || (Chunks[j][i]->ID_MATERIAL == 3) || (Chunks[j][i]->ID_MATERIAL == 4) || (Chunks[j][i]->ID_MATERIAL == 0))
				counter = 0;*/

			if (Chunks[j][i]->ID_MATERIAL == 1)
			{
				counter++;
				UE_LOG(LogTemp, Warning, TEXT("Point number %d found in (%d, %d)"), counter, j, i);
				FirstPoint = FVector2D(j - 1, i - 1);
			}

		}
		counter = 0;
	}
	FixCrossing();
}

void ARoad::test_building_generation()
{

	int32 RandomNumber;
	FString MeshPath;
	for (int i = 10; i < Size - 10; i++)
	{
		for (int j = 10; j < Size - 10; j++)
		{
			if (Chunks[i][j]->ID_MATERIAL == 0)
			{
				UStaticMeshComponent* new_Building = DuplicateObject(Building, this);
				new_Building->RegisterComponent();
				//Building->SetWorldTransform(FTransform(FQuat(), FVector(2, 2, 4), FVector::ZeroVector));
				new_Building->SetWorldLocation(FVector(i * 500, j * 500, 100));
				new_Building->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
				new_Building->SetWorldScale3D(FVector(1.6, 1.6, (2 + (rand()) % 6)));
				if ((rand() % 5) == 1)
				{
					RandomNumber = FMath::RandRange(1, 4); // Generate a random number between 1 and 4
					MeshPath = FString::Printf(TEXT("/Script/Engine.StaticMesh'/Game/Assets/LevelPrototyping/Meshes/SM_Pine_Tree_1.SM_Pine_Tree_%d'"), RandomNumber);
					new_Building->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, *MeshPath));
					new_Building->SetWorldScale3D(FVector(1, 1, 1));
				}
				if ((rand() % 5) == 2)
				{
					RandomNumber = FMath::RandRange(1, 4); // Generate a random number between 1 and 4
					MeshPath = FString::Printf(TEXT("/Script/Foliage.FoliageType_InstancedStaticMesh'/Game/Assets/LevelPrototyping/Meshes/SM_Common_Tree_1_FoliageType.SM_Common_Tree_%d_FoliageType'"), RandomNumber);
					new_Building->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, *MeshPath));
					new_Building->SetWorldScale3D(FVector(1, 1, 1));
				}
				UE_LOG(LogTemp, Warning, TEXT("Launched %d %d"), i, j);
			}
		}
	}
}