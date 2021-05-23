// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Weapon/STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

ASTUBaseWeapon::ASTUBaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void ASTUBaseWeapon::Fire()
{
    UE_LOG(LogBaseWeapon, Display, TEXT("Fire!"));
    MakeShot();
}

void ASTUBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
}

void ASTUBaseWeapon::MakeShot()
{
    if (!GetWorld()) return;

    const ACharacter* Player = Cast<ACharacter>(GetOwner());

    if (!Player) return;

    const AController* Controller = Player->GetController<APlayerController>();

    if (!Controller) return;

    FVector ViewLocation;
    FRotator ViewRotation;
    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
    const FVector TraceStart = ViewLocation;
    const FVector TraceDirection = ViewRotation.Vector();
    const FVector TraceEnd = TraceStart + TraceDirection * MaxTraceDistance;

    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.AddIgnoredActor(GetOwner());
    FHitResult HitResult;
    GetWorld()->LineTraceSingleByChannel(HitResult,
                                         TraceStart,
                                         TraceEnd,
                                         ECollisionChannel::ECC_Visibility,
                                         CollisionQueryParams);

    if (HitResult.bBlockingHit)
    {
        
        DrawDebugLine(GetWorld(),
                      SocketTransform.GetLocation(),
                      HitResult.ImpactPoint,
                      FColor::Red,
                      false,
                      3.f,
                      0,
                      3.f);
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.f, 24, FColor::Red, false, 5.f);
        UE_LOG(LogBaseWeapon, Display, TEXT("Bone: %s"), *HitResult.BoneName.ToString());
    }
    else
    {
        DrawDebugLine(GetWorld(),
                      SocketTransform.GetLocation(),
                      TraceEnd,
                      FColor::Red,
                      false,
                      3.f,
                      0,
                      3.f);
    }
}
