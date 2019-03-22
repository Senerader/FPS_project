// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	int32 CurrentIndex = BlackboardComp->GetValueAsInt(Index.SelectedKeyName);
	UE_LOG(LogTemp, Warning, TEXT("%i is waypoint index"), CurrentIndex);
	return EBTNodeResult::Succeeded;
}


