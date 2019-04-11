// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGamemode.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "ActorPool.h"

AInfiniteTerrainGamemode::AInfiniteTerrainGamemode()
{
	NavMeshVolumePool= CreateDefaultSubobject<UActorPool>(FName("NavMeshVolume Pool"));
}

void AInfiniteTerrainGamemode::AddToPool(ANavMeshBoundsVolume * NavMeshVolume)
{
	NavMeshVolumePool->Add(NavMeshVolume);
}

void AInfiniteTerrainGamemode::PopulateVolumePool()
{
	TActorIterator<ANavMeshBoundsVolume> NavmeshIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (NavmeshIterator)
	{
		AddToPool(*NavmeshIterator);
		++NavmeshIterator;
	}
}