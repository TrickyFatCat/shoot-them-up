#pragma once
#include "Characters/STUPlayerState.h"

class STUUtils
{
public:
    template <typename T>
    static T* GetSTUPlayerComponent(AActor* PlayerPawn)
    {
        if (!PlayerPawn) return nullptr;

        return Cast<T>(PlayerPawn->GetComponentByClass(T::StaticClass()));
    }

    static bool AreEnemies(AController* ControllerA, AController* ControllerB)
    {
        if (!ControllerA || !ControllerB || ControllerA == ControllerB) return false;

        ASTUPlayerState* PlayerStateA = Cast<ASTUPlayerState>(ControllerA->PlayerState);
        ASTUPlayerState* PlayerStateB = Cast<ASTUPlayerState>(ControllerB->PlayerState);

        return PlayerStateA && PlayerStateB && PlayerStateA->GetTeamID() != PlayerStateB->GetTeamID();
    }

    static FText TextFromInt(const int32 Number) { return FText::FromString(FString::FromInt(Number)); }
};
