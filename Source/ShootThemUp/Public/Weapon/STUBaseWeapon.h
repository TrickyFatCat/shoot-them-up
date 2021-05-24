// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
    UFUNCTION(BlueprintGetter)
    float GetRateOfFire() const { return RateOfFire; }
    UFUNCTION(BlueprintSetter)
    void SetRateOfFire(const float NewRate);

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
    UPROPERTY(EditDefaultsOnly, BlueprintGetter=GetRateOfFire, BlueprintSetter=SetRateOfFire)
    float RateOfFire = 1.f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float BulletSpread = 6.f;

    void MakeShot();
    APlayerController* GetPlayerController() const;
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator &ViewRotation) const;
    FVector GetMuzzleWorldLocation() const;
    bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const;
    void DealDamage(const FHitResult& HitResult);
    float GetTimeBetweenShots() const { return TimeBetweenShots; }

private:
    FTimerHandle ShotTimerHandle;
    float TimeBetweenShots = 1.f;
};
