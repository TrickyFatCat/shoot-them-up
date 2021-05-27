// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Animations/STUChangeWeaponAnimNotify.h"

void USTUChangeWeaponAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
}
