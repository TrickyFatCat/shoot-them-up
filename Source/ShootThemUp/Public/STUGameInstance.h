// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STUGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    FName GetMenuLevelName() const { return MenuLevelName; }
    FName GetStartLevelName() const { return StartLevelName; }
    
protected:
    UPROPERTY(EditDefaultsOnly, Category="Game")
    FName MenuLevelName = NAME_None;
    UPROPERTY(EditDefaultsOnly, Category="Game")
    FName StartLevelName = NAME_None;
};
