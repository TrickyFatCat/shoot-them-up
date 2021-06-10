// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animations/STUAnimNotify.h"
#include "STURagdollEnablingNotify.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTURagdollEnablingNotify : public USTUAnimNotify
{
    GENERATED_BODY()

public:
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
