// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "AI/Tasks/STUNextLocationTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

USTUNextLocationTask::USTUNextLocationTask()
{
    NodeName = "Choose Next Location";
}

EBTNodeResult::Type USTUNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* Controller = OwnerComp.GetAIOwner();
    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

    if (!Controller || !Blackboard) return EBTNodeResult::Failed;

    APawn* Pawn = Controller->GetPawn();

    if (!Pawn) return EBTNodeResult::Failed;

    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(Pawn);

    if (!NavSystem) return EBTNodeResult::Failed;

    FNavLocation TargetLocation;
    FVector Location = Pawn->GetActorLocation();

    if (!bIsSelfCentered)
    {
        AActor* CenteredActor = Cast<AActor>(Blackboard->GetValueAsObject(CenteredActorKey.SelectedKeyName));

        if (!CenteredActor) return EBTNodeResult::Failed;

        Location = CenteredActor->GetActorLocation();
    }
    const bool bLocationFound = NavSystem->GetRandomReachablePointInRadius(
                                                                        Pawn->GetActorLocation(),
                                                                             Radius,
                                                                          TargetLocation);

    if (!bLocationFound) return EBTNodeResult::Failed;

    Blackboard->SetValueAsVector(TargetLocationKey.SelectedKeyName, TargetLocation);
    return EBTNodeResult::Succeeded;
}
