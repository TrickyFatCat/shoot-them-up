// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/STUBaseWidget.h"
#include "STUCoreTypes.h"
#include "STUPlayerHudWidget.generated.h"

class USTUHealthComponent;
class UProgressBar;

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUPlayerHudWidget : public USTUBaseWidget
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

    UFUNCTION(BlueprintImplementableEvent, Category="UI")
    void OnTakeDamage();

protected:
    UPROPERTY(meta=(BindWidget))
    UProgressBar* ProgressBarHealth = nullptr;
    UPROPERTY(Transient, meta=(BindWidgetAnim))
    UWidgetAnimation* DamageAnimation = nullptr;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    float HealthColorThreshold = 0.25f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    FLinearColor HealthColorNormal = FLinearColor::Green;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    FLinearColor HealthColorCritical = FLinearColor::Red;
    virtual void NativeOnInitialized() override;

private:
    void OnHealthChanged(const float Health, const float DeltaHealth);
    void OnShieldChanged(const float Shield, const float DeltaShield);
    void OnNewPawn(APawn* Pawn);
    void UpdateHealthBar() const;
    UFUNCTION(BlueprintPure, Category="UI")
    int32 GetKills() const;
    
    const TCHAR PrefixSymbol = '0';
    UFUNCTION(BlueprintCallable, Category="UI")
    FString FormatAmmoNumber(const int32 BulletsNumber, const int32 MaxLen = 3) const;
};
