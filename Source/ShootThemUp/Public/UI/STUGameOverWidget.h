// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/STUBaseWidget.h"
#include "STUCoreTypes.h"
#include "STUGameOverWidget.generated.h"

class UVerticalBox;
class UButton;

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUGameOverWidget : public USTUBaseWidget 
{
	GENERATED_BODY()

protected:
    UPROPERTY(meta=(BindWidget))
    UVerticalBox* PlayerStatBox;
    
    UPROPERTY(meta=(BindWidget))
    UButton* ButtonResetLevel;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

    virtual void NativeOnInitialized() override;

private:
    void OnMatchStateChanged(ESTUMatchState NewState);
    void UpdatePlayerStat() const;

    UFUNCTION()
    void OnResetLevel();
};
