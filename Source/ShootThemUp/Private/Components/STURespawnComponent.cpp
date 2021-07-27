// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Components/STURespawnComponent.h"
#include "STUGameModeBase.h"


USTURespawnComponent::USTURespawnComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTURespawnComponent::StartRespawn(const int32 RespawnTime)
{
    if (!GetWorld()) return;

    RespawnCountDown = RespawnTime;
    GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle,
                                           this,
                                           &USTURespawnComponent::RespawnTimerUpdate,
                                           1.f,
                                           true);
}

void USTURespawnComponent::RespawnTimerUpdate()
{
    if(--RespawnCountDown == 0)
    {
        if(!GetWorld()) return;

        GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);
        ASTUGameModeBase* GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());

        if (!GameMode) return;

        GameMode->RespawnRequest(Cast<AController>(GetOwner()));
    }
}
