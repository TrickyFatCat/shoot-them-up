// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "UI/STUPlayerHudWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"

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

bool USTUPlayerHudWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
    const APawn* PlayerPawn = GetOwningPlayerPawn();

    if (!PlayerPawn) return false;

    const USTUWeaponComponent* WeaponComponent = Cast<USTUWeaponComponent>(PlayerPawn->GetComponentByClass(USTUWeaponComponent::StaticClass()));

    if (!WeaponComponent) return false;

    return WeaponComponent->GetWeaponUIData(UIData);
}

USTUHealthComponent* USTUPlayerHudWidget::GetHealthComponent() const
{
    const APawn* PlayerPawn = GetOwningPlayerPawn();

    if (!PlayerPawn) return nullptr;

    return Cast<USTUHealthComponent>(PlayerPawn->GetComponentByClass(USTUHealthComponent::StaticClass()));
}
