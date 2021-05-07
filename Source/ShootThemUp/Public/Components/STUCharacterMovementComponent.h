// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "STUCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUCharacterMovementComponent : public UCharacterMovementComponent
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintGetter)
    float GetSprintFactor() const { return SprintFactor; }
    UFUNCTION(BlueprintSetter)
    void SetSprintFactor(float NewFactor);
    virtual float GetMaxSpeed() const override;

private:
    const float MinSprintFactor = 1.f;
    const float MaxSprintFactor = 10.f;
    UPROPERTY(EditDefaultsOnly,
        BlueprintGetter=GetSprintFactor,
        BlueprintSetter=SetSprintFactor,
        Category="Movement",
        meta=(ClampMin="1.0", ClampMax="10.0", AllowPrivateAccess="true"))
    float SprintFactor = 2.f;
};
