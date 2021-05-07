// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Components/STUCharacterMovementComponent.h"
#include "Characters/STUBaseCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogCharacterMovement, All, All);

void USTUCharacterMovementComponent::SetSprintFactor(float NewFactor)
{
    if (NewFactor < MinSprintFactor || NewFactor > MaxSprintFactor)
    {
        UE_LOG(LogCharacterMovement,
               Error,
               TEXT("Illegal new value for SprintFactor %.2f. It can't be < %.2f or > %.2f. SprintFactor of %s wasn't changed"),
               NewFactor,
               MinSprintFactor,
               MaxSprintFactor,
               *GetOwner()->GetName());
        NewFactor = SprintFactor;
    }

    SprintFactor = NewFactor;
}

float USTUCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const ASTUBaseCharacter* Player = Cast<ASTUBaseCharacter>(GetPawnOwner());
    return Player != nullptr && Player->GetIsSprinting() ? MaxSpeed * SprintFactor : MaxSpeed;
}
