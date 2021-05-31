// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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

protected:
    USTUHealthComponent* GetHealthComponent() const;
};
