// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon/STUCoreTypes.h"
#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;
class APlayerController;


UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    ASTUBaseWeapon();
    virtual void StartFire();
    virtual void StopFire();
    void ReloadClip();
    bool CanReload() const { return CurrentAmmo.ClipAmmo < CurrentAmmo.ClipSize && CurrentAmmo.ClipsNumber > 0; }
    bool EnoughAmmo() const { return CurrentAmmo.ClipAmmo > 0 && CurrentAmmo.ClipsNumber > 0; }
    FOnClipEmptySignature OnClipEmpty;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Component", meta=(AllowPrivateAccess="true"))
    USkeletalMeshComponent* WeaponMesh = nullptr;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FName MuzzleSocketName = "MuzzleSocket";
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float MaxTraceDistance = 5000.f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float DamageAmount = 10.f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float BulletSpread = 6.f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FAmmoData DefaultAmmo{20, 20, 5, false};

    virtual void MakeShot();
    APlayerController* GetPlayerController() const;
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator &ViewRotation) const;
    FVector GetMuzzleWorldLocation() const;
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const;

    void DecreaseAmmo();
    void IncreaseAmmo(const int32 DeltaAmmo);
    bool IsClipEmpty() const { return CurrentAmmo.ClipAmmo <= 0; }
    bool IsEmpty() const { return CurrentAmmo.ClipsNumber <= 0 && !CurrentAmmo.bIsInfinite && IsClipEmpty(); }
private:
    FAmmoData CurrentAmmo;
};
