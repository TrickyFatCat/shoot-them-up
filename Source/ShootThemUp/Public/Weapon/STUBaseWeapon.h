// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "STUCoreTypes.h"
#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;
class APlayerController;
class UNiagaraSystem;
class UNiagaraComponent;
class USoundCue;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    ASTUBaseWeapon();
    virtual void StartFire();
    virtual void StopFire();
    void ReloadClip();
    bool CanReload() const { return WeaponAmmo.ClipAmmo < WeaponAmmo.ClipAmmoMax && WeaponAmmo.InventoryAmmo > 0; }
    bool EnoughAmmo() const { return WeaponAmmo.ClipAmmo > 0 && WeaponAmmo.InventoryAmmo > 0; }
    bool IsEmpty() const { return WeaponAmmo.InventoryAmmo <= 0 && !WeaponAmmo.bIsInfinite && IsClipEmpty(); }
    bool IsClipEmpty() const { return WeaponAmmo.ClipAmmo <= 0; }
    bool IncreaseAmmo(const int32 Amount);
    FWeaponUIData GetUIData() const { return WeaponUIData; }
    FAmmoData GetAmmoData() const { return WeaponAmmo; }
    FOnClipEmptySignature OnClipEmpty;

    virtual void SetZoom(const bool bIsEnabled);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Component", meta=(AllowPrivateAccess="true"))
    USkeletalMeshComponent* WeaponMesh = nullptr;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FName MuzzleSocketName = "MuzzleSocket";
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon")
    float MaxTraceDistance = 5000.f;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    float DamageAmount = 10.f;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    float BulletSpread = 6.f;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    FAmmoData WeaponAmmo{20, 20, 100, 100, false};
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    FWeaponUIData WeaponUIData;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
    UNiagaraSystem* MuzzleFX;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sound")
    USoundCue* ShootSound = nullptr;

    UNiagaraComponent* SpawnMuzzleFX();

    virtual void MakeShot();
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator &ViewRotation) const;
    FVector GetMuzzleWorldLocation() const;
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const;

    void DecreaseAmmo();
    bool IsInventoryFull() const { return WeaponAmmo.InventoryAmmo >= WeaponAmmo.InventoryAmmoMax; }
};
