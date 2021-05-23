// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Weapon/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "GameFramework/Character.h"


USTUWeaponComponent::USTUWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void USTUWeaponComponent::Fire()
{
    if (!CurrentWeapon) return;

    CurrentWeapon->Fire();
}

void USTUWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    Owner = Cast<ACharacter>(GetOwner());
    SpawnWeapon();
}

void USTUWeaponComponent::SpawnWeapon()
{
    if (!GetWorld() || !Owner) return;

    CurrentWeapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);

    if (!CurrentWeapon) return;
    
    const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    CurrentWeapon->AttachToComponent(Owner->GetMesh(), AttachmentRules, WeaponSocketName);
    CurrentWeapon->SetOwner(GetOwner());
}
