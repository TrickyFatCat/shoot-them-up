// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

class USTUHealthComponent;
class ASTUBaseWeapon;
class USTUWeaponComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ASTUBaseCharacter(const FObjectInitializer& ObjInit);

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Materials
public:
    void SetPlayerColor(const FLinearColor& TeamColor);
protected:
    UPROPERTY(EditDefaultsOnly, Category="Material")
    FName MaterialColorName = "Paint Color";

    // Movement
public:
    UFUNCTION(BlueprintPure, Category="Movement")
    virtual bool GetIsSprinting() const;
    UFUNCTION(BlueprintPure, Category="Movement")
    float GetCurrentVelocity() const { return GetVelocity().Size(); }

    UFUNCTION(BlueprintPure, Category="Movement")
    float GetMovementDirection() const;
protected:
    bool bIsMovingForward = false;
    bool bIsSprinting = false;
    virtual void StartSprinting();
    virtual void StopSprinting();

    // Health and damage
public:
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
    USTUHealthComponent* HealthComponent = nullptr;
    UPROPERTY(EditDefaultsOnly, Category="Animation")
    UAnimMontage* DeathAnimMontage = nullptr;
    virtual void OnDeath();
    virtual void OnHealthChanged(const float Health, const float DeltaHealth);
    virtual void OnShieldChanged(const float Shield, const float DeltaShield);
    USTUHealthComponent* GetHealthComponent() const { return HealthComponent; }
private:
    const float DestroyTime = 5.f;

    // Landing damage
    UPROPERTY(EditDefaultsOnly, Category="Damage")
    FVector2D LandedDamageVelocity = FVector2D(900.f, 1200.f);
    UPROPERTY(EditDefaultsOnly, Category="Damage")
    FVector2D LandedDamage = FVector2D(10.f, 100.f);
    UFUNCTION()
    void OnGroundLanded(const FHitResult& Hit);

    // Weapon
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
    USTUWeaponComponent* WeaponComponent = nullptr;
};
