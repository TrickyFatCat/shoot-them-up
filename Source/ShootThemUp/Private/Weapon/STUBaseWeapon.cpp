// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Weapon/STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

ASTUBaseWeapon::ASTUBaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void ASTUBaseWeapon::StartFire()
{
}

void ASTUBaseWeapon::StopFire()
{
}

void ASTUBaseWeapon::SetZoom(const bool bIsEnabled)
{
}

void ASTUBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
    WeaponAmmo.ClipAmmo = WeaponAmmo.ClipAmmoMax;
    WeaponAmmo.InventoryAmmo = WeaponAmmo.InventoryAmmoMax;
}

UNiagaraComponent* ASTUBaseWeapon::SpawnMuzzleFX()
{
    return UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFX,
                                                        WeaponMesh,
                                                        MuzzleSocketName,
                                                        FVector::ZeroVector,
                                                        FRotator::ZeroRotator,
                                                        EAttachLocation::SnapToTarget,
                                                        true);
}

void ASTUBaseWeapon::MakeShot()
{
}

bool ASTUBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());

    if (!Character) return false;

    if (Character->IsPlayerControlled())
    {
        const APlayerController* Controller = Character->GetController<APlayerController>();

        if (!Controller) return false;

        Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    }
    else
    {
        ViewLocation = GetMuzzleWorldLocation();
        ViewRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
    }

    return true;
}

FVector ASTUBaseWeapon::GetMuzzleWorldLocation() const
{
    return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool ASTUBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;

    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

    TraceStart = ViewLocation;
    const FVector TraceDirection = ViewRotation.Vector();
    TraceEnd = TraceStart + TraceDirection * MaxTraceDistance;
    return true;
}

void ASTUBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const
{
    const UWorld* World = GetWorld();

    if (!World) return;

    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.AddIgnoredActor(GetOwner());
    CollisionQueryParams.bReturnPhysicalMaterial = true;
    World->LineTraceSingleByChannel(HitResult,
                                    TraceStart,
                                    TraceEnd,
                                    ECollisionChannel::ECC_Visibility,
                                    CollisionQueryParams);
}

void ASTUBaseWeapon::DecreaseAmmo()
{
    if (IsEmpty()) return;

    WeaponAmmo.ClipAmmo = FMath::Max(--WeaponAmmo.ClipAmmo, 0);

    if (IsClipEmpty() && !IsEmpty())
    {
        OnClipEmpty.Broadcast(this);
    }
}

void ASTUBaseWeapon::ReloadClip()
{
    StopFire();

    if (!WeaponAmmo.bIsInfinite)
    {
        if (WeaponAmmo.InventoryAmmo == 0) return;

        const int32 DeltaAmmo = WeaponAmmo.ClipAmmoMax - WeaponAmmo.ClipAmmo;
        const int32 RestoredAmmo = WeaponAmmo.InventoryAmmo < DeltaAmmo ? WeaponAmmo.InventoryAmmo : DeltaAmmo;
        WeaponAmmo.InventoryAmmo = FMath::Max(WeaponAmmo.InventoryAmmo - DeltaAmmo, 0);
        WeaponAmmo.ClipAmmo = FMath::Max(WeaponAmmo.ClipAmmo + RestoredAmmo, WeaponAmmo.ClipAmmoMax);
    }
    else
    {
        WeaponAmmo.ClipAmmo = WeaponAmmo.ClipAmmoMax;
    }
}

bool ASTUBaseWeapon::IncreaseAmmo(const int32 Amount)
{
    if (IsInventoryFull() || WeaponAmmo.bIsInfinite) return false;


    if (IsEmpty())
    {
        WeaponAmmo.InventoryAmmo = FMath::Min(Amount, WeaponAmmo.InventoryAmmoMax + WeaponAmmo.ClipAmmoMax);
        OnClipEmpty.Broadcast(this);
    }
    else
    {
        WeaponAmmo.InventoryAmmo = FMath::Min(WeaponAmmo.InventoryAmmo + Amount, WeaponAmmo.InventoryAmmoMax);
    }

    return true;
}
