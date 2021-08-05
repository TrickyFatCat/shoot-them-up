// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "UI/STUPlayerStatRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void USTUPlayerStatRowWidget::SetPlayerName(const FText& Text) const
{
    if (!TextPlayerName) return;

    TextPlayerName->SetText(Text);
}

void USTUPlayerStatRowWidget::SetKills(const FText& Text) const
{
    if (!TextKills) return;

    TextKills->SetText(Text);
}

void USTUPlayerStatRowWidget::SetDeaths(const FText& Text) const
{
    if (!TextDeaths) return;

    TextDeaths->SetText(Text);
}

void USTUPlayerStatRowWidget::SetTeam(const FText& Text) const
{
    if (!TextTeam) return;

    TextTeam->SetText(Text);
}

void USTUPlayerStatRowWidget::SetPlayerIndicatorVisibility(const bool bIsVisible) const
{
    if (!ImagePlayerIndicator) return;

    ImagePlayerIndicator->SetVisibility(bIsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void USTUPlayerStatRowWidget::SetTeamColor(const FLinearColor& TeamColor) const
{
    if (!ImageTeamColor) return;

    ImageTeamColor->SetColorAndOpacity(TeamColor);
}
