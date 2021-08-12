// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

class USTUWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UAudioComponent;

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
    GENERATED_BODY()
public:
    ASTURifleWeapon();
    virtual void StartFire() override;
    virtual void StopFire() override;

    UFUNCTION(BlueprintGetter)
    float GetRateOfFire() const { return RateOfFire; }

    UFUNCTION(BlueprintSetter)
    void SetRateOfFire(const float NewRate);
    
    virtual void SetZoom(const bool bIsEnabled) override;

protected:
    UPROPERTY(VisibleAnywhere, Category="VFX");
    USTUWeaponFXComponent* WeaponFXComponent = nullptr;
    UPROPERTY(EditDefaultsOnly, Category="VFX")
    UNiagaraSystem* TraceFX = nullptr;
    UPROPERTY(EditDefaultsOnly, Category="VFX")
    FString TraceTargetName = "TraceTarget";
    UPROPERTY(EditDefaultsOnly, Category="Weapon")
    float CameraFOVZoom = 50.f;
    UPROPERTY(EditDefaultsOnly, Category="Weapon")
    float BulletSpreadZoom = 2.f;
    virtual void BeginPlay() override;
    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
    UPROPERTY()
    UAudioComponent* ShootAudioComponent = nullptr;
    
    UPROPERTY(EditDefaultsOnly, BlueprintGetter=GetRateOfFire, BlueprintSetter=SetRateOfFire)
    float RateOfFire = 8.f;
    FTimerHandle ShotTimerHandle;
    float TimeBetweenShots = 1.f;
    void DealDamage(const FHitResult& HitResult);

    UPROPERTY()
    UNiagaraComponent* MuzzleFXComponent;
    void InitFX();
    void SetFXActive(const bool bIsActive);

    void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);

    AController* GetController() const;

    float CameraFOVDefault = 90.f;
    float BulletSpreadDefault = BulletSpread;
};
