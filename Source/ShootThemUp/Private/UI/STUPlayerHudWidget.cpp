// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "UI/STUPlayerHudWidget.h"
#include "Components/STUHealthComponent.h"

float USTUPlayerHudWidget::GetNormalizedHealth() const
{
    const USTUHealthComponent* HealthComponent = GetHealthComponent();

    if (!HealthComponent) return 0.f;

    return HealthComponent->GetNormalizedHealth();
}

float USTUPlayerHudWidget::GetNormalizedShield() const
{
    const USTUHealthComponent* HealthComponent = GetHealthComponent();

    if (!HealthComponent) return 0.f;

    return HealthComponent->GetNormalizedShield();
}

USTUHealthComponent* USTUPlayerHudWidget::GetHealthComponent() const
{
    const APawn* PlayerPawn = GetOwningPlayerPawn();

    if (!PlayerPawn) return nullptr;

    return Cast<USTUHealthComponent>(PlayerPawn->GetComponentByClass(USTUHealthComponent::StaticClass()));
}
