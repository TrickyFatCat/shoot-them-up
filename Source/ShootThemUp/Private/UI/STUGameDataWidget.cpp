// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "UI/STUGameDataWidget.h"
#include "STUGameModeBase.h"
#include "Characters/STUPlayerState.h"

int32 USTUGameDataWidget::GetCurrentRoundNum() const
{
    ASTUGameModeBase* GameMode = GetSTUGameMode();
    return GameMode ? GameMode->GetCurrentRoundNum() : -1;
}

int32 USTUGameDataWidget::GetTotalRoundsNum() const
{
    ASTUGameModeBase* GameMode = GetSTUGameMode();
    return GameMode ? GameMode->GetGameData().RoundsNumber : -1;
}

int32 USTUGameDataWidget::GetRoundSecondsRemaining() const
{
    ASTUGameModeBase* GameMode = GetSTUGameMode();
    return GameMode ? GameMode->GetRoundSecondsRemaining() : -1;
}

ASTUGameModeBase* USTUGameDataWidget::GetSTUGameMode() const
{
    return GetWorld() ? Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

ASTUPlayerState* USTUGameDataWidget::GetSTUPlayerState() const
{
    return GetOwningPlayer() ? Cast<ASTUPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
