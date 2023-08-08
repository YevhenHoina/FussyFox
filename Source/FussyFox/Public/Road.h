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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	/*
	//UPROPERTY(EditAnywhere, Meta = (TEXT("Straight prospect road")))
	UPROPERTY(EditAnyWhere)
	UStaticMeshComponent* prospect_straight;

	//UPROPERTY(EditAnywhere, Meta = (TEXT("Turn tight prospect road")))
	UPROPERTY(EditAnyWhere)
	UStaticMeshComponent* prospect_right;

	//UPROPERTY(EditAnywhere, Meta = (TEXT("Trun left prospect road")))
	UPROPERTY(EditAnyWhere)
	UStaticMeshComponent* prospect_left;

	//UPROPERTY(EditAnywhere, Meta = (TEXT("T-crossing prospect road")))
	UPROPERTY(EditAnyWhere)
	UStaticMeshComponent* prospect_left_right;

	//UPROPERTY(EditAnywhere, Meta = (TEXT("X-crossing prospect road")))
	UPROPERTY(EditAnyWhere)
	UStaticMeshComponent* prospect_crossing;*/

	//UPROPERTY(EditAnywhere, Meta = (TEXT("Straight prospect road")))
	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMesh* prospect_straight;

	//UPROPERTY(EditAnywhere, Meta = (TEXT("Turn tight prospect road")))
	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMesh* prospect_right;

	//UPROPERTY(EditAnywhere, Meta = (TEXT("Trun left prospect road")))
	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMesh* prospect_left;

	//UPROPERTY(EditAnywhere, Meta = (TEXT("T-crossing prospect road")))
	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMesh* prospect_left_right;

	//UPROPERTY(EditAnywhere, Meta = (TEXT("X-crossing prospect road")))
	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMesh* prospect_crossing;
	//UPROPERTY(EditAnywhere, Meta = (TEXT("End of prospect road")))
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMesh* prospect_end;

	UStaticMesh* Prospects[6] =
	{
		prospect_straight,
		prospect_right,
		prospect_left,
		prospect_left_right,
		prospect_crossing,
		prospect_end,
	};
	void SetDefaultMesh(FString AssetPath, UStaticMesh* MeshToCheck);
};
