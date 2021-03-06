// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Weapon/STULauncherWeapon.h"
#include "Weapon/STUProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void ASTULauncherWeapon::StartFire()
{
    MakeShot();
}

void ASTULauncherWeapon::StopFire()
{
}

void ASTULauncherWeapon::MakeShot()
{
    UWorld* World = GetWorld();
    
    if (!World) return;

    if (IsClipEmpty())
    {
        StopFire();
        UGameplayStatics::PlaySoundAtLocation(World, NoAmmoSound, GetActorLocation());
        return;
    }

    FVector TraceStart, TraceEnd;

    if (!GetTraceData(TraceStart, TraceEnd))
    {
        StopFire();
        return;
    }

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    const FVector MuzzleLocation = GetMuzzleWorldLocation();
    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const FVector Direction = (EndPoint - MuzzleLocation).GetSafeNormal();
    const FTransform SpawnTransform(FRotator::ZeroRotator, MuzzleLocation);
    ASTUProjectile* Projectile = World->SpawnActorDeferred<ASTUProjectile>(ProjectileClass, SpawnTransform);
    if (Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }

    DecreaseAmmo();
    SpawnMuzzleFX();
    UGameplayStatics::SpawnSoundAttached(ShootSound, WeaponMesh, MuzzleSocketName);
}
