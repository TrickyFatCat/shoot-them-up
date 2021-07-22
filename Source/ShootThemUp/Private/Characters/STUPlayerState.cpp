// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Characters/STUPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUPlayerState, All, All)

void ASTUPlayerState::LogStatistics()
{
    UE_LOG(LogSTUPlayerState, Display, TEXT("TeamID: %i | Kills: %i | Deaths: %i"), TeamID, KillsNumber, DeathsNumber);
}
