// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "AI/STUAIController.h"
#include "AI/STUAICharacter.h"
#include "Components/STUAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/STURespawnComponent.h"

ASTUAIController::ASTUAIController()
{
    STUAIPerceptionComponent = CreateDefaultSubobject<USTUAIPerceptionComponent>("STUAIPerceptionComponent");
    SetPerceptionComponent(*STUAIPerceptionComponent);
    RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("STURespawnComponent");
    bWantsPlayerState = true;
}

void ASTUAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    AActor* TargetActor = GetTargetActor();
    SetFocus(TargetActor);
}

void ASTUAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const auto STUCharacter = Cast<ASTUAICharacter>(InPawn);

    if (STUCharacter)
    {
        RunBehaviorTree(STUCharacter->BehaviorTreeAsset);
    }
}

AActor* ASTUAIController::GetTargetActor() const
{
    if (!GetBlackboardComponent()) return nullptr;

    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(TargetEneemyKeyName));
}
