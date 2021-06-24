// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Components/STUAIPerceptionComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* USTUAIPerceptionComponent::GetClosestEnemy() const
{
    TArray<AActor*> PerceivedActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceivedActors);

    if (PerceivedActors.Num() == 0) return nullptr;

    AAIController* Controller = Cast<AAIController>(GetOwner());

    if (!Controller) return nullptr;

    APawn* Pawn = Controller->GetPawn();

    if (!Pawn) return nullptr;

    float ClosestDistance = MAX_FLT;
    AActor* ClosestPawn = nullptr;

    for (AActor* PerceivedActor : PerceivedActors)
    {
        USTUHealthComponent* HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PerceivedActor);

        if (HealthComponent && !HealthComponent->GetIsDead()) // TODO: Check if enemy or not
        {
            const float CurrentDistance = (PerceivedActor->GetActorLocation() - Pawn->GetActorLocation()).Size();

            if (CurrentDistance < ClosestDistance)
            {
                ClosestDistance = CurrentDistance;
                ClosestPawn = PerceivedActor;
            }
        }
    }

    return ClosestPawn;
}
