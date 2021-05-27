﻿// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/STUEquipFinishedAnimNotify.h"
#include "Animations/STUChangeWeaponAnimNotify.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

USTUWeaponComponent::USTUWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void USTUWeaponComponent::StartFire()
{
    if (!CanFire()) return;

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
    if (!CanEquip()) return;

    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    bEquipInProgress = true;
    PlayAnimMontage(EquipAnimMontage);
}

void USTUWeaponComponent::EquipPreviousWeapon()
{
    if (!CanEquip()) return;

    CurrentWeaponIndex = CurrentWeaponIndex == 0 ? Weapons.Num() - 1 : CurrentWeaponIndex - 1;
    bEquipInProgress = true;
    PlayAnimMontage(EquipAnimMontage);
}

void USTUWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    Owner = Cast<ACharacter>(GetOwner());
    InitAnimations();
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

void USTUWeaponComponent::PlayAnimMontage(UAnimMontage* Animation) const
{
    if (!Owner) return;

    Owner->PlayAnimMontage(Animation);
}

void USTUWeaponComponent::InitAnimations()
{
    if (!EquipAnimMontage) return;

    const TArray<FAnimNotifyEvent> NotifyEvents = EquipAnimMontage->Notifies;

    for (auto NotifyEvent : NotifyEvents)
    {
        auto WeaponChangeNotify = Cast<USTUChangeWeaponAnimNotify>(NotifyEvent.Notify);
        auto EquipFinishedNotify = Cast<USTUEquipFinishedAnimNotify>(NotifyEvent.Notify);

        if (WeaponChangeNotify)
        {
            WeaponChangeNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnChangeWeapons);
        }

        if (EquipFinishedNotify)
        {
            EquipFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);
        }
    }
}

void USTUWeaponComponent::OnChangeWeapons(USkeletalMeshComponent* MeshComponent)
{
    if (!Owner) return;

    if (Owner->GetMesh() != MeshComponent) return;
    
    EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
    if (!Owner) return;

    if (Owner->GetMesh() != MeshComponent) return;

    bEquipInProgress = false;
}
