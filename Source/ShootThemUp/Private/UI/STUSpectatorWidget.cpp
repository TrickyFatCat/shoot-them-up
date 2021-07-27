// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "UI/STUSpectatorWidget.h"
#include "STUUtils.h"
#include "Components/STURespawnComponent.h"

bool USTUSpectatorWidget::GetRespawnTime(int32& CountDown)
{
    USTURespawnComponent* RespawnComponent = STUUtils::GetSTUPlayerComponent<USTURespawnComponent>(GetOwningPlayer());

    if(!RespawnComponent || !RespawnComponent->IsRespawnActive()) return false;

    CountDown = RespawnComponent->GetRespawnCountDown();
    return true;
}
