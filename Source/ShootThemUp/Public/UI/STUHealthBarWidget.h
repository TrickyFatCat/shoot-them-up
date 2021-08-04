// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUHealthBarWidget.generated.h"

class UProgressBar;

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUHealthBarWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetHealthAndShieldPercent(const float HealthPercent, const float ShieldPercent);
protected:
    UPROPERTY(meta=(BindWidget))
    UProgressBar* ProgressBarHealth = nullptr;
    UPROPERTY(meta=(BindWidget))
    UProgressBar* ProgressBarShield = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI", meta=(Tooltip="In percent"))
    float ShieldVisibilityThreshold = 0.8f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI", meta=(Tooltip="In percent"))
    float HealthVisibilityThreshold = 0.8f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    float HealthColorThreshold = 0.25f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    FLinearColor HealthColorNormal = FLinearColor::Green;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    FLinearColor HealthColorCritical = FLinearColor::Red;
};
