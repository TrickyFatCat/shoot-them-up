// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUMenuWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUMenuWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeOnInitialized() override;
    
    UPROPERTY(meta=(BindWidget))
    UButton* ButtonStartGame = nullptr;
    
    UPROPERTY(meta=(BindWidget))
    UButton* ButtonQuitGame = nullptr;

private:
    UFUNCTION()
    void OnStartGame();

    UFUNCTION()
    void OnQuitGame();
};
