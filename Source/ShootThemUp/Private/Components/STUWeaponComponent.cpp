// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "GameFramework/Character.h"


USTUWeaponComponent::USTUWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void USTUWeaponComponent::StartFire()
{
    if (!CurrentWeapon) return;

    CurrentWeapon->StartFire();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void USTUWeaponComponent::StopFire()
{
    if (!CurrentWeapon) return;

    CurrentWeapon->StopFire();
}

void USTUWeaponComponent::EquipNextWeapon()
{
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::EquipPreviousWeapon()
{
    CurrentWeaponIndex = CurrentWeaponIndex == 0 ? Weapons.Num() - 1 : CurrentWeaponIndex - 1;
    EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    Owner = Cast<ACharacter>(GetOwner());
    SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CurrentWeapon = nullptr;
    for (ASTUBaseWeapon* Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }

    Weapons.Empty();
    Super::EndPlay(EndPlayReason);
}

void USTUWeaponComponent::SpawnWeapons()
{
    if (!GetWorld() || !Owner) return;

    for (auto WeaponClass : WeaponClasses)
    {
        ASTUBaseWeapon* Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);

        if (!Weapon) continue;

        Weapon->SetOwner(Owner);
        Weapons.Add(Weapon);
        AttachWeaponToSocket(Weapon, Owner->GetMesh(), ArmoryWeaponSocketName);
    }
}

void USTUWeaponComponent::AttachWeaponToSocket(ASTUBaseWeapon* Weapon,
                                               USkeletalMeshComponent* Mesh,
                                               const FName SocketName)
{
    const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(Mesh, AttachmentRules, SocketName);
}

void USTUWeaponComponent::EquipWeapon(const int32 WeaponIndex)
{
    if (!Owner || WeaponIndex >= Weapons.Num() || Weapons.Num() == 0) return;

    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Owner->GetMesh(), ArmoryWeaponSocketName);
    }

    CurrentWeapon = Weapons[WeaponIndex];
    AttachWeaponToSocket(CurrentWeapon, Owner->GetMesh(), EquippedWeaponSocketName);
}
