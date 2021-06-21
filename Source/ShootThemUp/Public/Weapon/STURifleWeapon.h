// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

class USTUWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;

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

protected:
    UPROPERTY(VisibleAnywhere, Category="VFX");
    USTUWeaponFXComponent* WeaponFXComponent = nullptr;
    UPROPERTY(EditDefaultsOnly, Category="VFX")
    UNiagaraSystem* TraceFX = nullptr;
    UPROPERTY(EditDefaultsOnly, Category="VFX")
    FString TraceTargetName = "TraceTarget";
    virtual void BeginPlay() override;
    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
    UPROPERTY(EditDefaultsOnly, BlueprintGetter=GetRateOfFire, BlueprintSetter=SetRateOfFire)
    float RateOfFire = 8.f;
    FTimerHandle ShotTimerHandle;
    float TimeBetweenShots = 1.f;
    void DealDamage(const FHitResult& HitResult);

    UPROPERTY()
    UNiagaraComponent* MuzzleFXComponent;
    void InitMuzzleFX();
    void SetMuzzleFXVisibility(const bool bIsVisible);

    void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);
};
