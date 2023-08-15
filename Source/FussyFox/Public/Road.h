// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"


#include "Road.generated.h"

UCLASS()
class FUSSYFOX_API ARoad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoad();



	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

 
 
	UPROPERTY(EditAnyWhere)
		UStaticMeshComponent* InitialMeshComponent;

	UPROPERTY(EditAnyWhere)
		int BorderSize = 5;
 
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	


	int Size = 60;
	

private:
	void SetDefaultMesh(FString AssetPath, UStaticMesh* MeshToCheck);
	int getRandomNumber();
	void GenerateSurface();

	// void BuildLine(FVector2D FirstPoint, FVector2D SecondPoint);
	// void FixCrossing();
	
};
