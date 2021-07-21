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
    
private:
    int32 TeamID;
    FLinearColor TeamColor;
};
