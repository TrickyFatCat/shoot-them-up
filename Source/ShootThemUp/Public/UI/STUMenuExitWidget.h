// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUMenuExitWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUMenuExitWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeOnInitialized() override;
    UPROPERTY(meta=(BindWidget))
    UButton* ButtonExitToMenu = nullptr;

private:
    UFUNCTION()
    void OnExitToMenu();
};
