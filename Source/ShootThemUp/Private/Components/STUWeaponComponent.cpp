// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "Weapon/STUCoreTypes.h"
#include "GameFramework/Character.h"
#include "Animations/STUEquipFinishedAnimNotify.h"
#include "Animations/STUChangeWeaponAnimNotify.h"
#include "Animations/STUReloadAnimNotify.h"
#include "Animations/AnimUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

USTUWeaponComponent::USTUWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void USTUWeaponComponent::StartFire()
{
    if (!CanFire()) return;

    if (CurrentWeapon->IsEmpty()) return;
    
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

void USTUWeaponComponent::Reload()
{
    if (!CanReload()) return;
    CurrentWeapon->StopFire();
    ReloadClip();
}

bool USTUWeaponComponent::GetWeaponUIData(FWeaponUIData& WeaponUIData) const
{
    if (CurrentWeapon)
    {
        WeaponUIData = CurrentWeapon->GetUIData();
        return true;
    }

    return false;
}

bool USTUWeaponComponent::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
    if (CurrentWeapon)
    {
        AmmoData = CurrentWeapon->GetAmmoData();
        return true;
    }

    return false;
}

void USTUWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    Owner = Cast<ACharacter>(GetOwner());
    checkf(EquipAnimMontage, TEXT("Equipping anim montage isn't set in weapon component of %s"), *Owner->GetName())
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

    for (auto Data : WeaponData)
    {
        ASTUBaseWeapon* Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(Data.WeaponClass);

        if (!Weapon) continue;

        Weapon->OnClipEmpty.AddUObject(this, &USTUWeaponComponent::OnEmptyClip);
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
    if (!Owner || WeaponIndex >= Weapons.Num() || Weapons.Num() <= 0) return;

    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Owner->GetMesh(), ArmoryWeaponSocketName);
    }

    CurrentWeapon = Weapons[WeaponIndex];
    const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data)
    {
        return Data.WeaponClass == CurrentWeapon->GetClass();
    });
    CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;
    AttachWeaponToSocket(CurrentWeapon, Owner->GetMesh(), EquippedWeaponSocketName);
}

void USTUWeaponComponent::PlayAnimMontage(UAnimMontage* Animation) const
{
    if (!Owner) return;

    Owner->PlayAnimMontage(Animation);
}

void USTUWeaponComponent::InitAnimations()
{
    auto WeaponChangeNotify = AnimUtils::FindFirstNotifyByClass<USTUChangeWeaponAnimNotify>(EquipAnimMontage);

    if (WeaponChangeNotify)
    {
        WeaponChangeNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnChangeWeapons);
    }
    else
    {
        UE_LOG(LogWeaponComponent,
               Error,
               TEXT("Change weapon anim notify not found in %s"),
               *EquipAnimMontage->GetName());
        checkNoEntry();
    }

    auto EquipFinishedNotify = AnimUtils::FindFirstNotifyByClass<USTUEquipFinishedAnimNotify>(EquipAnimMontage);

    if (EquipFinishedNotify)
    {
        EquipFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);
    }
    else
    {
        UE_LOG(LogWeaponComponent,
               Error,
               TEXT("Equip finished anim notify not found in %s"),
               *EquipAnimMontage->GetName());
        checkNoEntry();
    }

    for (auto Data : WeaponData)
    {
        auto ReloadFinishNotify = AnimUtils::FindFirstNotifyByClass<USTUReloadAnimNotify>(Data.ReloadAnimMontage);
        if (ReloadFinishNotify)
        {
            ReloadFinishNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnReloadFinished);
        }
        else
        {
            UE_LOG(LogWeaponComponent,
                   Error,
                   TEXT("Reload anim notify not found in %s"),
                   *Data.ReloadAnimMontage->GetName());
            checkNoEntry();
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

void USTUWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{
    if (!Owner || !CurrentWeapon) return;

    if (Owner->GetMesh() != MeshComponent) return;

    CurrentWeapon->ReloadClip();
    bReloadInProgress = false;
}

void USTUWeaponComponent::OnEmptyClip()
{
    ReloadClip();
}

void USTUWeaponComponent::ReloadClip()
{
    if (!CanReload()) return;

    bReloadInProgress = true;
    PlayAnimMontage(CurrentReloadAnimMontage);
}
