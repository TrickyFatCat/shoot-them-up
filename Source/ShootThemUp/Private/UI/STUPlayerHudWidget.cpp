// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "UI/STUPlayerHudWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"
#include "Components/ProgressBar.h"
#include "Characters/STUPlayerState.h"

float USTUPlayerHudWidget::GetNormalizedHealth() const
{
    const USTUHealthComponent* HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(
        GetOwningPlayerPawn());

    if (!HealthComponent) return 0.f;

    return HealthComponent->GetNormalizedHealth();
}

float USTUPlayerHudWidget::GetNormalizedShield() const
{
    const USTUHealthComponent* HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(
        GetOwningPlayerPawn());

    if (!HealthComponent) return 0.f;

    return HealthComponent->GetNormalizedShield();
}

bool USTUPlayerHudWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
    const USTUWeaponComponent* WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(
        GetOwningPlayerPawn());

    if (!WeaponComponent) return false;

    return WeaponComponent->GetWeaponUIData(UIData);
}

bool USTUPlayerHudWidget::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
    const USTUWeaponComponent* WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(
        GetOwningPlayerPawn());

    if (!WeaponComponent) return false;

    return WeaponComponent->GetWeaponAmmoData(AmmoData);
}

bool USTUPlayerHudWidget::IsPlayerAlive() const
{
    const USTUHealthComponent* HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(
        GetOwningPlayerPawn());
    return HealthComponent && !HealthComponent->GetIsDead();
}

bool USTUPlayerHudWidget::IsPlayerSpectating() const
{
    const APlayerController* Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}

void USTUPlayerHudWidget::NativeOnInitialized()
{
    if (GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USTUPlayerHudWidget::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }

    USTUHealthComponent* HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());

    if (HealthComponent)
    {
        HealthComponent->OnHealthChanged.AddUObject(this, &USTUPlayerHudWidget::OnHealthChanged);
        HealthComponent->OnShieldChanged.AddUObject(this, &USTUPlayerHudWidget::OnShieldChanged);
    }
}

void USTUPlayerHudWidget::OnHealthChanged(const float Health, const float DeltaHealth)
{
    if (DeltaHealth < 0)
    {
        OnTakeDamage();
    }

    UpdateHealthBar();
}

void USTUPlayerHudWidget::OnShieldChanged(const float Shield, const float DeltaShield)
{
    if (DeltaShield < 0)
    {
        OnTakeDamage();
    }
}

void USTUPlayerHudWidget::OnNewPawn(APawn* Pawn)
{
    USTUHealthComponent* HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(Pawn);

    if (HealthComponent)
    {
        if (!HealthComponent->OnHealthChanged.IsBoundToObject(this))
        {
            HealthComponent->OnHealthChanged.AddUObject(this, &USTUPlayerHudWidget::OnHealthChanged);
        }

        if (!HealthComponent->OnShieldChanged.IsBoundToObject(this))
        {
            HealthComponent->OnShieldChanged.AddUObject(this, &USTUPlayerHudWidget::OnShieldChanged);
        }
    }

    UpdateHealthBar();
}

void USTUPlayerHudWidget::UpdateHealthBar()
{
    if (ProgressBarHealth)
    {
        ProgressBarHealth->SetFillColorAndOpacity(GetNormalizedHealth() > HealthColorThreshold
                                                      ? HealthColorNormal
                                                      : HealthColorCritical);
    }
}

int32 USTUPlayerHudWidget::GetKills() const
{
    const APlayerController* PlayerController = GetOwningPlayer();

    if (!PlayerController) return -1;

    const ASTUPlayerState* PlayerState = Cast<ASTUPlayerState>(PlayerController->PlayerState);
    return PlayerState ? PlayerState->GetKillsNumber() : -1;
}
