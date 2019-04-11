// Fill out your copyright notice in the Description page of Project Settings.

#include "Grass.h"


// Sets default values for this component's properties
UGrass::UGrass()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrass::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SpawnGrass();
}


// Called every frame
void UGrass::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGrass::SpawnGrass()
{
	for (int32 i = 0; i < SpawnNumber; i++)
	{
		FVector SpawnLocation = FMath::RandPointInBox(BoxLimits);
		AddInstance(FTransform(SpawnLocation));
	}
}

