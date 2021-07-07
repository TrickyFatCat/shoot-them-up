// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"

#include "STUCheckAmmoDecorator.generated.h"

class ASTUBaseWeapon;

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUCheckAmmoDecorator : public UBTDecorator
{
    GENERATED_BODY()

public:
    USTUCheckAmmoDecorator();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    TSubclassOf<ASTUBaseWeapon> WeaponToCheck = nullptr;

    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
