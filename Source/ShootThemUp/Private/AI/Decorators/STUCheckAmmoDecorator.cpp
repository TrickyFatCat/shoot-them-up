// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "AI/Decorators/STUCheckAmmoDecorator.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUWeaponComponent.h"

USTUCheckAmmoDecorator::USTUCheckAmmoDecorator()
{
    NodeName = "Check Ammo";
}

bool USTUCheckAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    AAIController* Controller = OwnerComp.GetAIOwner();

    if (!Controller) return false;

    USTUWeaponComponent* WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());

    if (!WeaponComponent) return false;

    return WeaponComponent->IsAmmoNeeded(WeaponToCheck);
}
