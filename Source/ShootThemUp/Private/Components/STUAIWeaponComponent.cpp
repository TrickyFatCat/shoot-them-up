// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Components/STUAIWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"

void USTUAIWeaponComponent::StartFire()
{
    if (!CanFire()) return;

    if (CurrentWeapon->IsClipEmpty())
    {
        EquipNextWeapon();
    }
    else
    {
        CurrentWeapon->StartFire();
    }
}

void USTUAIWeaponComponent::EquipNextWeapon()
{
    if (!CanEquip()) return;

    int32 NextWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();

    while(NextWeaponIndex != CurrentWeaponIndex)
    {
        if (!Weapons[NextWeaponIndex]->IsEmpty()) break;

        NextWeaponIndex = (NextWeaponIndex + 1) % Weapons.Num();
    }

    if (CurrentWeaponIndex != NextWeaponIndex)
    {
        CurrentWeaponIndex = NextWeaponIndex;
        bEquipInProgress = true;
        PlayAnimMontage(EquipAnimMontage);
    }
}

void USTUAIWeaponComponent::EquipPreviousWeapon()
{
    Super::EquipPreviousWeapon();
}
