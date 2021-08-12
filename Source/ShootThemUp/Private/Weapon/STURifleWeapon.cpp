// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Weapon/STURifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

ASTURifleWeapon::ASTURifleWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

void ASTURifleWeapon::StartFire()
{
    InitFX();
    MakeShot();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASTURifleWeapon::MakeShot, TimeBetweenShots, true);
}

void ASTURifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    SetFXActive(false);
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
    FVector TraceFXEnd = TraceEnd;


    if (HitResult.bBlockingHit)
    {
        TraceFXEnd = HitResult.ImpactPoint;
        DealDamage(HitResult);
        WeaponFXComponent->PlayImpactFX(HitResult);
    }

    SpawnTraceFX(GetMuzzleWorldLocation(), TraceFXEnd);
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

void ASTURifleWeapon::SetZoom(const bool bIsEnabled)
{
    APlayerController* PlayerController = Cast<APlayerController>(GetController());

    if (!PlayerController) return;

    APlayerCameraManager* PlayerCameraManager = PlayerController->PlayerCameraManager;

    if (!PlayerCameraManager) return;

    if (bIsEnabled)
    {
        CameraFOVDefault = PlayerCameraManager->GetFOVAngle();
        BulletSpreadDefault = BulletSpread;
    }

    PlayerCameraManager->SetFOV(bIsEnabled ? CameraFOVZoom : CameraFOVDefault);
    BulletSpread = bIsEnabled ? BulletSpreadZoom : BulletSpreadDefault;
}

void ASTURifleWeapon::DealDamage(const FHitResult& HitResult)
{
    AActor* DamagedActor = HitResult.GetActor();

    if (!DamagedActor) return;

    DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetController(), this);
}

void ASTURifleWeapon::InitFX()
{
    if (!MuzzleFXComponent)
    {
        MuzzleFXComponent = SpawnMuzzleFX();
    }

    if (!ShootAudioComponent)
    {
        ShootAudioComponent = UGameplayStatics::SpawnSoundAttached(ShootSound, WeaponMesh, MuzzleSocketName);
    }

    SetFXActive(true);
}

void ASTURifleWeapon::SetFXActive(const bool bIsActive)
{
    if (MuzzleFXComponent)
    {
        MuzzleFXComponent->SetPaused(!bIsActive);
        MuzzleFXComponent->SetVisibility(bIsActive, true);
    }

    if (ShootAudioComponent)
    {
        bIsActive ? ShootAudioComponent->Play() : ShootAudioComponent->Stop();
    }
}

void ASTURifleWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
    UNiagaraComponent* TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
        GetWorld(),
        TraceFX,
        TraceStart);

    if (TraceFXComponent)
    {
        TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
    }
}

AController* ASTURifleWeapon::GetController() const
{
    const APawn* Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}
