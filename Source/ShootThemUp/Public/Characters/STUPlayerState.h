// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "STUPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    void SetTeamID(int32 ID) { TeamID = ID; }
    int32 GetTeamID() const { return TeamID; }
    void SetTeamColor(FLinearColor Color) { TeamColor = Color; }
    FLinearColor GetTeamColor() const { return TeamColor; }
    
    void AddKill() { ++KillsNumber; }
    int32 GetKillsNumber() const { return KillsNumber; }
    void AddDeath() { ++DeathsNumber; }
    int32 GetDeathsNumber() const { return DeathsNumber; }

    void LogStatistics();
    
private:
    int32 TeamID;
    FLinearColor TeamColor;
    int32 KillsNumber = 0;
    int32 DeathsNumber = 0;
};
