// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STUChangeWeaponService.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUChangeWeaponService : public UBTService
{
	GENERATED_BODY()
	
public:
    USTUChangeWeaponService();
    
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(ClampMin="0.0", ClampMax="1.0"))
	float ChangeProbability = 0.5f;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
