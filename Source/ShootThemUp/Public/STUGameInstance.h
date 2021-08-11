// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STUCoreTypes.h"
#include "STUGameInstance.generated.h"

class USoundClass;

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

    void ToggleVolume() const;
    
protected:
    UPROPERTY(EditDefaultsOnly, Category="Game", meta=(Tooltip="Level names must be usnique!"))
    TArray<FLevelData> LevelsData;
    UPROPERTY(EditDefaultsOnly, Category="Game")
    FName MenuLevelName = NAME_None;
    UPROPERTY(EditDefaultsOnly, Category="Sound")
    USoundClass* MasterSoundClass = nullptr;

private:
    FLevelData StartLevelData;
};
