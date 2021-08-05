// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerStatRowWidget.generated.h"

class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUPlayerStatRowWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetPlayerName(const FText& Text) const;
    void SetKills(const FText& Text) const;
    void SetDeaths(const FText& Text) const;
    void SetTeam(const FText& Text) const;
    void SetPlayerIndicatorVisibility(const bool bIsVisible) const;
    void SetTeamColor(const FLinearColor& TeamColor) const;

protected:
    UPROPERTY(meta=(BindWidget))
    UTextBlock* TextPlayerName = nullptr;
    
    UPROPERTY(meta=(BindWidget))
    UTextBlock* TextKills = nullptr;
    
    UPROPERTY(meta=(BindWidget))
    UTextBlock* TextDeaths = nullptr;
    
    UPROPERTY(meta=(BindWidget))
    UTextBlock* TextTeam = nullptr;
    
    UPROPERTY(meta=(BindWidget))
    UImage* ImagePlayerIndicator = nullptr;
    
    UPROPERTY(meta=(BindWidget))
    UImage* ImageTeamColor = nullptr;
};
