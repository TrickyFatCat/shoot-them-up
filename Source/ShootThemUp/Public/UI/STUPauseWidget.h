// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/STUBaseWidget.h"
#include "STUPauseWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUPauseWidget : public USTUBaseWidget 
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta=(BindWidget))
    UButton* ClearPauseButton = nullptr;

    virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
    void OnClearPause();
};
