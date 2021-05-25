// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Weapon/STULauncherWeapon.h"
#include "Weapon/STUProjectile.h"
#include "Kismet/GameplayStatics.h"

void ASTULauncherWeapon::StartFire()
{
    MakeShot();
}

void ASTULauncherWeapon::StopFire()
{
}

void ASTULauncherWeapon::MakeShot()
{
    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    AActor* Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ProjectileClass, SpawnTransform);
    // Set projectile params
    UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
}
