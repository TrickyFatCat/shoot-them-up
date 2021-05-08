// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Components/STUHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogResourceComponent, All, All)

USTUHealthComponent::USTUHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    Health = bCustomInitialValue ? InitialHealth : MaxHealth;
}
