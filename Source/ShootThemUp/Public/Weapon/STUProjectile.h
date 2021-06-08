// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class USTUWeaponFXComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUProjectile : public AActor
{
    GENERATED_BODY()

public:
    ASTUProjectile();
    void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; }

protected:
    virtual void BeginPlay() override;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
    USphereComponent* CollisionComponent = nullptr;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
    UProjectileMovementComponent* MovementComponent = nullptr;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    USTUWeaponFXComponent* WeaponFXComponent = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    float DamageAmount = 50.f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    float DamageRadius = 250.f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    bool bDoFullDamage = false;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    float DefaultLifeSpan = 5.f;

private:
    FVector ShotDirection = FVector::ZeroVector;
    UFUNCTION()
    void OnProjectileHit(UPrimitiveComponent* HitComponent,
                         AActor* OtherActor,
                         UPrimitiveComponent* OtherComp,
                         FVector NormalImpulse,
                         const FHitResult& Hit);

    AController* GetController() const;
};
