// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPS_projectGameMode.h"
#include "InfiniteTerrainGamemode.generated.h"

class UActorPool;
class ANavMeshBoundsVolume;
/**
 * 
 */
UCLASS()
class FPS_PROJECT_API AInfiniteTerrainGamemode : public AFPS_projectGameMode
{
	GENERATED_BODY()
	
public:
	//Default constructor
	AInfiniteTerrainGamemode();

	//Used to add all existing actors in a single pool
	UFUNCTION(BlueprintCallable, Category = "Pool")
	void PopulateVolumePool();

protected:
	//Reference to NavMesh pool
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NavMesh Pool")
	UActorPool* NavMeshVolumePool;


private:
	//Used to add existing dynamic navigation mesh to the different pool
	void AddToPool(ANavMeshBoundsVolume *NavMeshVolume);
};
