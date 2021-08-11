// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "STUGameInstance.h"
#include "Sound/STUSoundFuncLib.h"

void USTUGameInstance::ToggleVolume() const
{
    USTUSoundFuncLib::ToggleSoundClassVolume(MasterSoundClass);
}
