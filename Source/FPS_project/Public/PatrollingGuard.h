// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "PatrollingGuard.generated.h"

/**
 * 
 */
UCLASS()
class FPS_PROJECT_API APatrollingGuard : public ATP_ThirdPersonCharacter
{
	GENERATED_BODY()
	
public:
	TArray<AActor*> GetPatrolPointsCPP();

private:
	UPROPERTY(EditInstanceOnly, Category = "Patrol Route")
	TArray <AActor*> PatrolPointsCPP;
};
