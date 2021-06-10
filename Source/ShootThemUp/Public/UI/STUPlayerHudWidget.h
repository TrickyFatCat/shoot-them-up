// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/STUWeaponComponent.h"
#include "Weapon/STUCoreTypes.h"
#include "STUPlayerHudWidget.generated.h"

class USTUHealthComponent;

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUPlayerHudWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category="UI")
    float GetNormalizedHealth() const;
    UFUNCTION(BlueprintPure, Category="UI")
    float GetNormalizedShield() const;
    UFUNCTION(BlueprintPure, Category="UI")
    bool GetWeaponUIData(FWeaponUIData& UIData) const;
    UFUNCTION(BlueprintPure, Category="UI")
    bool GetWeaponAmmoData(FAmmoData& AmmoData) const;
    UFUNCTION(BlueprintPure, Category="UI")
    bool IsPlayerAlive() const;
    UFUNCTION(BlueprintPure, Category="UI")
    bool IsPlayerSpectating() const;

    virtual bool Initialize() override;
    UFUNCTION(BlueprintImplementableEvent, Category="UI")
    void OnTakeDamage();

private:
    void OnHealthChanged(const float Health, const float DeltaHealth);
    void OnShieldChanged(const float Shield, const float DeltaShield);
};
