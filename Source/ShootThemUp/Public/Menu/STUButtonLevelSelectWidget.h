// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CoreTypes.h"
#include "STUCoreTypes.h"

#include "STUButtonLevelSelectWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUButtonLevelSelectWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    virtual void NativeOnInitialized() override;
    
public:
    FOnLevelSelectedSignature OnLevelSelected;
    void SetLevelData(const FLevelData& Data);
    FLevelData GetLevelData() const { return LevelData; } 
    void SetSelected(bool bIsSelected);
protected:
    
    UPROPERTY(meta=(BindWidget))
    UButton* ButtonSelectLevel = nullptr;
    UPROPERTY(meta=(BindWidget))
    UTextBlock* TextLevelDisplayName = nullptr;
    UPROPERTY(meta=(BindWidget))
    UImage* ImageLevelPicture = nullptr;
    UPROPERTY(meta=(BindWidget))
    UImage* ImageFrame = nullptr;

private:
    FLevelData LevelData;

    UFUNCTION()
    void OnSelectButtonClicked();
};
