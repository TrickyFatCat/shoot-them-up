// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "AI/Decorators/STUResourcePercentDecorator.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUHealthComponent.h"

USTUResourcePercentDecorator::USTUResourcePercentDecorator()
{
    NodeName = "Check Resource Percent";
}

bool USTUResourcePercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
                                                              uint8* NodeMemory) const
{
    AAIController* Controller = OwnerComp.GetAIOwner();

    if (!Controller) return false;

    USTUHealthComponent* HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(Controller->GetPawn());

    if (!HealthComponent || HealthComponent->GetIsDead()) return false;

    bool bIsResourceLow = false;

    switch (ResourceToCheck)
    {
        case EResourceType::Health:
            bIsResourceLow = HealthComponent->GetNormalizedHealth() <= ResourceThreshold;
            break;
        case EResourceType::Shield:
            bIsResourceLow = HealthComponent->GetNormalizedShield() <= ResourceThreshold;
            break;
        default:
            break;
    }

    return bIsResourceLow; 
}
