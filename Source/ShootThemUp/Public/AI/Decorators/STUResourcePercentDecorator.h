// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STUResourcePercentDecorator.generated.h"

/**
 * 
 */

UENUM()
enum class EResourceType : uint8
{
    Health,
    Shield
};

UCLASS()
class SHOOTTHEMUP_API USTUResourcePercentDecorator : public UBTDecorator
{
    GENERATED_BODY()

public:
    USTUResourcePercentDecorator();

protected:
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    float ResourceThreshold = 0.6f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    EResourceType ResourceToCheck = EResourceType::Health;
};
