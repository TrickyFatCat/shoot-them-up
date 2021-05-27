// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Weapon/STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Viewports.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

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

void ASTUBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
    CurrentAmmo = DefaultAmmo;
}

void ASTUBaseWeapon::MakeShot()
{

}

APlayerController* ASTUBaseWeapon::GetPlayerController() const
{
    const ACharacter* Player = Cast<ACharacter>(GetOwner());

    if (!Player) return nullptr;

    return Player->GetController<APlayerController>();
}

bool ASTUBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
    const APlayerController* Controller = GetPlayerController();

    if (!Controller) return false;

    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
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
    World->LineTraceSingleByChannel(HitResult,
                                    TraceStart,
                                    TraceEnd,
                                    ECollisionChannel::ECC_Visibility,
                                    CollisionQueryParams);
}

void ASTUBaseWeapon::DecreaseAmmo()
{
    CurrentAmmo.ClipAmmo = FMath::Max(--CurrentAmmo.ClipAmmo, 0);

    UE_LOG(LogTemp, Warning, TEXT("Ammo: %d/%d"), CurrentAmmo.ClipAmmo, CurrentAmmo.ClipSize);

    if (IsClipEmpty() && !IsEmpty())
    {
        ReloadClip();
    }
}

void ASTUBaseWeapon::IncreaseAmmo(const int32 DeltaAmmo)
{
}

void ASTUBaseWeapon::ReloadClip()
{
    CurrentAmmo.ClipAmmo = CurrentAmmo.ClipSize;

    if (!CurrentAmmo.bIsInfinite)
    {
        CurrentAmmo.ClipsNumber--;
    }
}


