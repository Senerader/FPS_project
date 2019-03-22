// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "PatrolRouteComponent.h"
#include "Runtime/Engine/Classes/Components/ActorComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Checking if we have assigned struct data in the Path behaviour tree
	if (WaypointKey.SelectedKeyName.IsNone() || IndexKey.SelectedKeyName.IsNone()) { return EBTNodeResult::Failed; }

	//Getting and checking Blackboard PathData
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!ensure(BlackboardComp)){ return EBTNodeResult::Failed; }

	//Getting an array and checking whether it is empty
	TArray <AActor*> LocalPatrolPoints = GetPatrolPointsBlackboard(OwnerComp);
	if (LocalPatrolPoints.Num() == 0) { return EBTNodeResult::Failed; }

	//Setting the waypoint by current index
	int32 CurrentIndex = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, LocalPatrolPoints[CurrentIndex]);

	//Incrementing and clamping current index to cycle our waypoints
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
	//Finding the root component attached to an actor
	UPatrolRouteComponent* PatrolRouteComp = GuardAIOwner->GetPawn()->FindComponentByClass<UPatrolRouteComponent>();
	if (!ensure(PatrolRouteComp)) { return TArray<AActor*>(); }
	TArray <AActor*> LocalPatrolPoints = PatrolRouteComp->GetPatrolPointsCPP();
	return LocalPatrolPoints;
}


