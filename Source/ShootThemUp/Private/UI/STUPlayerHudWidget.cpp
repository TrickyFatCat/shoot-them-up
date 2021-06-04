// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "UI/STUPlayerHudWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"

float USTUPlayerHudWidget::GetNormalizedHealth() const
{
    const USTUHealthComponent* HealthComponent = GetComponentByClass<USTUHealthComponent>();

    if (!HealthComponent) return 0.f;

    return HealthComponent->GetNormalizedHealth();
}

float USTUPlayerHudWidget::GetNormalizedShield() const
{
    const USTUHealthComponent* HealthComponent = GetComponentByClass<USTUHealthComponent>();

    if (!HealthComponent) return 0.f;

    return HealthComponent->GetNormalizedShield();
}

bool USTUPlayerHudWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
    const USTUWeaponComponent* WeaponComponent = GetComponentByClass<USTUWeaponComponent>();

    if (!WeaponComponent) return false;

    return WeaponComponent->GetWeaponUIData(UIData);
}

bool USTUPlayerHudWidget::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
    const USTUWeaponComponent* WeaponComponent = GetComponentByClass<USTUWeaponComponent>();

    if (!WeaponComponent) return false;

    return WeaponComponent->GetWeaponAmmoData(AmmoData);
}

bool USTUPlayerHudWidget::IsPlayerAlive() const
{
    const USTUHealthComponent* HealthComponent = GetComponentByClass<USTUHealthComponent>();
    return HealthComponent && !HealthComponent->GetIsDead();
}

bool USTUPlayerHudWidget::IsPlayerSpectating() const
{
    const APlayerController* Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}