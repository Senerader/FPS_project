// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class USceneComponent;

UCLASS()
class FPS_PROJECT_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Construction")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn = 1, int MaxSpawn = 1, float Radius = 500);

private:
	//Checks if any object in proximity at the SpawnPoint
	bool IsInProximity(FVector SpawnLocation, float Radius);
	
	bool FindEmptyLocation(FVector& OutSpawnPoint, float Radius);

	void PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint);
};
