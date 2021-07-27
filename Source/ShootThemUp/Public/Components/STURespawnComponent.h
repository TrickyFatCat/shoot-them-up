// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STURespawnComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTURespawnComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USTURespawnComponent();

    void StartRespawn(const int32 RespawnTime);

private:
    FTimerHandle RespawnTimerHandle;
    int32 RespawnCountDown;
    void RespawnTimerUpdate();
};
