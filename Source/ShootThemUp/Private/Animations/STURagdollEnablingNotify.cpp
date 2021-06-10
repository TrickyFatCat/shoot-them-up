// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Animations/STURagdollEnablingNotify.h"

void USTURagdollEnablingNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::Notify(MeshComp, Animation);

    if (MeshComp)
    {
        MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        MeshComp->SetSimulatePhysics(true);
    }
}
