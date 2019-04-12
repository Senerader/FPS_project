// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavigationSystem.h"
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

void ATile::SetNavMeshPool(UActorPool * SettingPool)
{
	NavMeshVolumePool = SettingPool;

	PositionNavMeshVolume();
}

void ATile::PositionNavMeshVolume()
{
	NavMeshBoundsVolume = NavMeshVolumePool->Checkout();
	if (NavMeshBoundsVolume == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] Pool for checkout was empty inside the Tile C++"), *GetName());
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("[%s] Checked out {%s}"), *GetName(), *NavMeshBoundsVolume->GetName());
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavigationBoundsOffset);
	GetWorld()->GetNavigationSystem()->Build();
}

//Function places actor based on the global world coordinates, uses struct which describes the random values of actor's geometry
void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	TArray<FSpawnPosition> SpawnPositions;

	GenerateRandomSpawnPositions(MinSpawn, MaxSpawn, MinScale, MaxScale, Radius, SpawnPositions);

	for (FSpawnPosition SpawnPosition : SpawnPositions)
	{
		PlaceActor(ToSpawn, SpawnPosition);
	}
}

void ATile::GenerateRandomSpawnPositions(int MinSpawn, int MaxSpawn, float MinScale, float MaxScale, float Radius, TArray<FSpawnPosition> &SpawnPositions)
{
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (int32 size = 0; size < NumberToSpawn; size++)
	{
		//Initializing actor's geometry
		FSpawnPosition SpawnPosition;

		SpawnPosition.Scale = FMath::RandRange(MinScale, MaxScale);
		bool Found = FindEmptyLocation(SpawnPosition.SpawnLocation, Radius * SpawnPosition.Scale);
		if (Found)
		{
			//Generating an actor with random scaling and rotation (scaling objects are predefined).
			SpawnPosition.Rotation = FMath::RandRange(-180.f, 180.f);

			SpawnPositions.Add(SpawnPosition);
		}
	}
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

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition)
{
	FVector GlobalSpawnPoint = ActorToWorld().TransformPosition(SpawnPosition.SpawnLocation);
	AActor* ActorSpawned = GetWorld()->SpawnActor<AActor>(ToSpawn, GlobalSpawnPoint, FRotator(0, SpawnPosition.Rotation, 0));
	ActorSpawned->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	ActorSpawned->SetActorScale3D(FVector(SpawnPosition.Scale));
}


