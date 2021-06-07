// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Pickups/STUAmmoPickup.h"
#include "STUUtils.h"
#include "Components/STUWeaponComponent.h"
#include "Components/STUHealthComponent.h"

ASTUAmmoPickup::ASTUAmmoPickup()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ASTUAmmoPickup::BeginPlay()
{
    Super::BeginPlay();
    
}

void ASTUAmmoPickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool ASTUAmmoPickup::ActivateEffect(APawn* PlayerPawn)
{
    const USTUHealthComponent* HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);

    if (!HealthComponent || HealthComponent->GetIsDead()) return false;

    USTUWeaponComponent* WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(PlayerPawn);

    if (!WeaponComponent) return false;

    return WeaponComponent->IncreaseWeaponAmmo(WeaponType, AmmoAmount);
}

