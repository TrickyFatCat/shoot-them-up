// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STUCoreTypes.h"
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
    
    FLevelData GetStartLevelData() const { return StartLevelData; }
    void SetStartLevelData(const FLevelData& LevelData) { StartLevelData = LevelData; }
    
    TArray<FLevelData> GetLevelsData() const { return LevelsData; }
    
protected:
    UPROPERTY(EditDefaultsOnly, Category="Game")
    TArray<FLevelData> LevelsData;
    UPROPERTY(EditDefaultsOnly, Category="Game")
    FName MenuLevelName = NAME_None;

private:
    FLevelData StartLevelData;
};
