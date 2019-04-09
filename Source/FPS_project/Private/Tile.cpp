// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
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

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, USceneComponent* StartOrigin)
{
	FVector Min = FVector(300, -1700, 0);
	FVector Max = FVector(3700, 1700, 0);
	FBox Bounds = FBox(Min, Max);
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (int size_t = 0; size_t < NumberToSpawn; size_t++)
	{
		FVector SpawnPoint = FMath::RandPointInBox(Bounds);
		UE_LOG(LogTemp, Warning, TEXT("%s relative"), *SpawnPoint.ToString());
		SpawnPoint.X += StartOrigin->GetComponentLocation().X;
		UE_LOG(LogTemp, Warning, TEXT("%s world2, %s relative2"), *StartOrigin->GetComponentLocation().ToString(), *SpawnPoint.ToString());
		AActor* ActorSpawned = GetWorld()->SpawnActor<AActor>(ToSpawn, SpawnPoint, FRotator::ZeroRotator);
		ActorSpawned->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	}
}

