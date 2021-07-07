// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_PickupIsActive.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API UEnvQueryTest_PickupIsActive : public UEnvQueryTest
{
    GENERATED_BODY()
    
public:
    UEnvQueryTest_PickupIsActive(const FObjectInitializer& ObjectInitializer);
    virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
