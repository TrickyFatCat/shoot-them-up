// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "UI/STUBaseWidget.h"
#include "STUMenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class USTUGameInstance;
class USTUButtonLevelSelectWidget;

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUMenuWidget : public USTUBaseWidget 
{
    GENERATED_BODY()

protected:
    virtual void NativeOnInitialized() override;
    
    UPROPERTY(meta=(BindWidget))
    UButton* ButtonStartGame = nullptr;
    
    UPROPERTY(meta=(BindWidget))
    UButton* ButtonQuitGame = nullptr;
    
    UPROPERTY(meta=(BindWidget))
    UHorizontalBox* BoxLevelsSelectors = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    TSubclassOf<UUserWidget> SelectButtonWidgetClass;

    UPROPERTY(Transient, meta=(BindWidgetAnim))
    UWidgetAnimation* HideAnimation = nullptr;

    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

private:
    UPROPERTY()
    TArray<USTUButtonLevelSelectWidget*>  LevelSelectButtons;
    
    UFUNCTION()
    void OnStartGame();

    UFUNCTION()
    void OnQuitGame();

    void InitLevelSelectButtons();
    void OnLevelSelected(const FLevelData& Data);
    USTUGameInstance* GetGameInstance() const;
};
