// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
    GENERATED_BODY()
public:
    virtual void StartFire() override;
    virtual void StopFire() override;

    UFUNCTION(BlueprintGetter)
    float GetRateOfFire() const { return RateOfFire; }

    UFUNCTION(BlueprintSetter)
    void SetRateOfFire(const float NewRate);

protected:
    virtual void BeginPlay() override;
    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
    UPROPERTY(EditDefaultsOnly, BlueprintGetter=GetRateOfFire, BlueprintSetter=SetRateOfFire)
    float RateOfFire = 8.f;
    FTimerHandle ShotTimerHandle;
    float TimeBetweenShots = 1.f;
    void DealDamage(const FHitResult& HitResult);
};
