// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "PatrollingGuard.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	TArray <AActor*> LocalPatrolPoints = GetPatrolPointsBlackboard(OwnerComp);

	if (LocalPatrolPoints.Num() == 0) { return EBTNodeResult::Failed; }

	//setting the waypoint by current index
	int32 CurrentIndex = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, LocalPatrolPoints[CurrentIndex]);

	//incrementing and clamping current index
	CurrentIndex++;
	CurrentIndex = CurrentIndex % LocalPatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, CurrentIndex);

	return EBTNodeResult::Succeeded;
}

TArray <AActor*> UChooseNextWaypoint::GetPatrolPointsBlackboard(UBehaviorTreeComponent& OwnerComp)
{
	//Getting an AI controller to cast its pawn to APatrollingGuard
	AAIController* GuardAIOwner = OwnerComp.GetAIOwner();
	if (!GuardAIOwner) { return TArray<AActor*>(); }
	//Casting pawn to an APatrollingGuard
	auto GuardCharacter = Cast<APatrollingGuard>(GuardAIOwner->GetPawn());
	if (!GuardCharacter) { return TArray<AActor*>(); }
	TArray <AActor*> LocalPatrolPoints = GuardCharacter->GetPatrolPointsCPP();
	return LocalPatrolPoints;
}


