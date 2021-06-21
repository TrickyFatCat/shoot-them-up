// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Weapon/STURifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraComponent.h"

ASTURifleWeapon::ASTURifleWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

void ASTURifleWeapon::StartFire()
{
    InitMuzzleFX();
    MakeShot();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASTURifleWeapon::MakeShot, TimeBetweenShots, true);
}

void ASTURifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    SetMuzzleFXVisibility(false);
}

void ASTURifleWeapon::SetRateOfFire(const float NewRate)
{
    if (NewRate <= 0) return;

    RateOfFire = NewRate;
    TimeBetweenShots = 1.f / RateOfFire;
}

void ASTURifleWeapon::BeginPlay()
{
    Super::BeginPlay();
    check(WeaponFXComponent);
    TimeBetweenShots = 1.f / RateOfFire;
}

void ASTURifleWeapon::MakeShot()
{
    UWorld* World = GetWorld();

    if (!World) return;
    
    if (IsClipEmpty())
    {
        StopFire();
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

    if (HitResult.bBlockingHit)
    {
        DealDamage(HitResult);
        WeaponFXComponent->PlayImpactFX(HitResult);
        // DrawDebugLine(World,
        //               GetMuzzleWorldLocation(),
        //               HitResult.ImpactPoint,
        //               FColor::Red,
        //               false,
        //               3.f,
        //               0,
        //               3.f);
        // DrawDebugSphere(World, HitResult.ImpactPoint, 10.f, 24, FColor::Red, false, 5.f);
    }
    else
    {
        DrawDebugLine(World,
                      GetMuzzleWorldLocation(),
                      TraceEnd,
                      FColor::Red,
                      false,
                      3.f,
                      0,
                      3.f
        );
    }

    DecreaseAmmo();
}

bool ASTURifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;

    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

    TraceStart = ViewLocation;
    const float ConeAngleRad = FMath::DegreesToRadians(BulletSpread * 0.5f);
    const FVector TraceDirection = FMath::VRandCone(ViewRotation.Vector(), ConeAngleRad);
    TraceEnd = TraceStart + TraceDirection * MaxTraceDistance;
    return true;
}

void ASTURifleWeapon::DealDamage(const FHitResult& HitResult)
{
    AActor* DamagedActor = HitResult.GetActor();

    if (!DamagedActor) return;

    DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}

void ASTURifleWeapon::InitMuzzleFX()
{
    if (!MuzzleFXComponent)
    {
        MuzzleFXComponent = SpawnMuzzleFX();
    }

    SetMuzzleFXVisibility(true);
}

void ASTURifleWeapon::SetMuzzleFXVisibility(const bool bIsVisible)
{
    if (MuzzleFXComponent)
    {
        MuzzleFXComponent->SetPaused(!bIsVisible);
        MuzzleFXComponent->SetVisibility(bIsVisible, true);
    }
}
