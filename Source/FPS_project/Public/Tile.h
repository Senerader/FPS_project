// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class USceneComponent;
class UActorPool;


USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()
	FVector SpawnLocation;
	float Rotation;
	float Scale;
};


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
	// Called when the game ends
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Construction")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn = 1, int MaxSpawn = 1, float Radius = 500, float MinScale = 1.f, float MaxScale = 1.f);

	UFUNCTION(BlueprintCallable, Category = "Construction")
	void PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int MinSpawn = 1, int MaxSpawn = 1, float Radius = 500);


	//Setting reference to the pool of dynamic navmesh on the level
	UFUNCTION(BlueprintCallable, Category = "NavMesh Pool")
	void SetNavMeshPool(UActorPool* SettingPool);
protected:
	//Default box spawning sizes
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector Min = FVector(300, -1700, 0);
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector Max = FVector(3700, 1700, 0);

	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
	FVector NavigationBoundsOffset = FVector(2000,0, 0);

private:
	//Checks if any object in proximity at the SpawnPoint
	bool IsInProximity(FVector SpawnLocation, float Radius);

	
	bool FindEmptyLocation(FVector& OutSpawnPoint, float Radius);

	//Template version of function used to determine the types to spawn and call functions accordingly, whether it is a pawn or an actor prop
	template <class T>
	void PlaceActorsRandomly(TSubclassOf<T> ToSpawn, int MinSpawn = 1, int MaxSpawn = 1, float Radius = 500, float MinScale = 1.f, float MaxScale = 1.f);

	void PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition);

	void PlaceActor(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition);

	void PositionNavMeshVolume();

	UActorPool* NavMeshVolumePool = nullptr;

	AActor* NavMeshBoundsVolume;
};
