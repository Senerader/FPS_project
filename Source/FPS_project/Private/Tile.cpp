// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "DrawDebugHelpers.h"
#include "ActorPool.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();


}

// Called when the game ends
void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	NavMeshVolumePool->Return(NavMeshBoundsVolume);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (int size_t = 0; size_t < NumberToSpawn; size_t++)
	{
		FVector SpawnPoint;
		float RandomScale = FMath::RandRange(MinScale, MaxScale);
		bool Found = FindEmptyLocation(SpawnPoint, Radius * RandomScale);
		if (Found)
		{
			//Generating an actor with random scaling and rotation (scaling objects are predefined).
			float RandomYawRotation = FMath::RandRange(-180.f, 180.f);
			PlaceActor(ToSpawn, SpawnPoint, RandomYawRotation, RandomScale);
		}
	}
}

void ATile::SetNavMeshPool(UActorPool * SettingPool)
{
	NavMeshVolumePool = SettingPool;

	PositionNavMeshVolume();
}

void ATile::PositionNavMeshVolume()
{
	NavMeshBoundsVolume = NavMeshVolumePool->Checkout();
	if (!ensure(NavMeshBoundsVolume)) { return; }
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation());
}

bool ATile::IsInProximity(FVector SpawnLocation, float Radius)
{
	FHitResult HitResult;
	FVector GlobalSpawnLocation = ActorToWorld().TransformPosition(SpawnLocation);
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		GlobalSpawnLocation,
		GlobalSpawnLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius)
	);
	return HasHit;
}

bool ATile::FindEmptyLocation(FVector & OutSpawnPoint, float Radius)
{
	FVector Min = FVector(300, -1700, 0);
	FVector Max = FVector(3700, 1700, 0);
	FBox Bounds = FBox(Min, Max);
	const int MAX_ATTEMPTS = 50;
	for (int32 i = 0; i < MAX_ATTEMPTS; i++)
	{
		FVector PossibleSpawnPoint = FMath::RandPointInBox(Bounds);
		if (!IsInProximity(PossibleSpawnPoint, Radius))
		{
			OutSpawnPoint = PossibleSpawnPoint;
			return true;
		}
	}
	return false;
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float Rotation, float Scale)
{
	FVector GlobalSpawnPoint = ActorToWorld().TransformPosition(SpawnPoint);
	AActor* ActorSpawned = GetWorld()->SpawnActor<AActor>(ToSpawn, GlobalSpawnPoint, FRotator(0, Rotation, 0));
	ActorSpawned->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	ActorSpawned->SetActorScale3D(FVector(Scale));
}


