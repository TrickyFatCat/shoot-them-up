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
    Super::NativeOnInitialized();

    if (GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USTUPlayerHudWidget::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }
}

void USTUPlayerHudWidget::OnHealthChanged(const float Health, const float DeltaHealth)
{
    if (DeltaHealth < 0)
    {
        OnTakeDamage();

        if (!IsAnimationPlaying(DamageAnimation))
        {
            PlayAnimation(DamageAnimation);
        }
    }

    UpdateHealthBar();
}

void USTUPlayerHudWidget::OnShieldChanged(const float Shield, const float DeltaShield)
{
    if (DeltaShield < 0)
    {
        OnTakeDamage();
        
        if (!IsAnimationPlaying(DamageAnimation))
        {
            PlayAnimation(DamageAnimation);
        }
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

    ProgressBarHealth->SetFillColorAndOpacity(HealthColorNormal); // It's a hack, but it works
    // UpdateHealthBar();  // Do not uncomment right now. Must to figure out how to control creation sequence.
    // Apparently, HUD creates earlier than Resource UObjects in HealthComponent as a result -> crash
}

void USTUPlayerHudWidget::UpdateHealthBar() const
{
    if (ProgressBarHealth)
    {
        const FLinearColor NewColor = GetNormalizedHealth() > HealthColorThreshold
                                          ? HealthColorNormal
                                          : HealthColorCritical;
        ProgressBarHealth->SetFillColorAndOpacity(NewColor);
    }
}

int32 USTUPlayerHudWidget::GetKills() const
{
    const APlayerController* PlayerController = GetOwningPlayer();

    if (!PlayerController) return -1;

    const ASTUPlayerState* PlayerState = Cast<ASTUPlayerState>(PlayerController->PlayerState);
    return PlayerState ? PlayerState->GetKillsNumber() : -1;
}

FString USTUPlayerHudWidget::FormatAmmoNumber(const int32 BulletsNumber, const int32 MaxLen) const
{
    FString BulletsString = FString::FromInt(BulletsNumber);
    const int32 AddSymbolNumber = MaxLen - BulletsString.Len();

    if (AddSymbolNumber > 0)
    {
        BulletsString = FString::ChrN(AddSymbolNumber, PrefixSymbol).Append(BulletsString);
    }

    return BulletsString;
}
