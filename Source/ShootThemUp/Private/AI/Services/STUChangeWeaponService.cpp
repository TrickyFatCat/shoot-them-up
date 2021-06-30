// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "AI/Services/STUChangeWeaponService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/STUAIWeaponComponent.h"
#include "STUUtils.h"

USTUChangeWeaponService::USTUChangeWeaponService()
{
    NodeName = "Change Weapon";
}

void USTUChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    AAIController* Controller = OwnerComp.GetAIOwner();
    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

    if (Controller)
    {
        USTUWeaponComponent* WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(
            Controller->GetPawn());

        const float DiceRoll = FMath::FRand();

        if (WeaponComponent && DiceRoll <= ChangeProbability && ChangeProbability > 0.f)
        {
            WeaponComponent->EquipNextWeapon();
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
