// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Objects/Resource.h"
#include "STUHealthComponent.generated.h"

class UCameraShakeBase;
class UPhysicalMaterial;

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, float)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnShieldChanged, float, float)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USTUHealthComponent();

private:
    virtual void BeginPlay() override;

    // Health
public:
    UFUNCTION(BlueprintPure)
    float GetHealth() const { return HealthObject->GetValue(); }

    UFUNCTION(BlueprintPure)
    float GetMaxHealth() const { return HealthObject->GetValueMax(); }

    UFUNCTION(BlueprintPure, Category="Health")
    float GetNormalizedHealth() const { return HealthObject->GetNormalizedValue(); }

    UFUNCTION(BlueprintCallable, Category="Health")
    void DecreaseHealth(const float DeltaHealth, AController* InstigatorController);
    
    UFUNCTION(BlueprintCallable, Category="Health")
    bool IncreaseHealth(const float DeltaHealth, const bool bClampToMax);
    
    UFUNCTION(BlueprintPure)
    bool GetIsDead() const { return GetHealth() <= 0.f; }

    FOnDeath OnDeath;
    FOnHealthChanged OnHealthChanged;
    void BroadcastOnHealthChanged(const float CurrentHealth, const float DeltaHealth);

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
    FResourceData HealthData;
    UPROPERTY()
    UResource* HealthObject = nullptr;

    // Shield 
public:
    UFUNCTION(BlueprintPure)
    float GetShield() const { return ShieldObject->GetValue(); }

    UFUNCTION(BlueprintPure)
    float GetMaxShield() const { return ShieldObject->GetValueMax(); }

    UFUNCTION(BlueprintPure, Category="Shield")
    float GetNormalizedShield() const { return ShieldObject->GetNormalizedValue(); }

    UFUNCTION(BlueprintCallable, Category="Shield")
    void DecreaseShield(const float DeltaShield, AController* InstigatorController);
    FOnShieldChanged OnShieldChanged;
    void BroadcastOnShieldChanged(const float CurrentShield, const float DeltaShield);

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
    FResourceData ShieldData;
    UPROPERTY()
    UResource* ShieldObject = nullptr;

    // Damage
private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX", meta=(AllowPrivateAccess="true"))
    TSubclassOf<UCameraShakeBase> DamageCameraShake;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
    TMap<UPhysicalMaterial*, float> DamageModifiers;
    
    void PlayCameraShake() const;
    
    UFUNCTION()
    void OnTakeAnyDamage(AActor* DamageActor,
                         float Damage,
                         const UDamageType* DamageType,
                         AController* InstigatedBy,
                         AActor* DamageCauser);


    UFUNCTION()
    void OnTakePointDamage(AActor* DamagedActor,
                           float Damage,
                           class AController* InstigatedBy,
                           FVector HitLocation,
                           class UPrimitiveComponent* FHitComponent,
                           FName BoneName,
                           FVector ShotFromDirection,
                           const class UDamageType* DamageType,
                           AActor* DamageCauser);
    
    UFUNCTION()
    void OnTakeRadialDamage(AActor* DamagedActor,
                            float Damage,
                            const class UDamageType* DamageType,
                            FVector Origin,
                            FHitResult HitInfo,
                            class AController* InstigatedBy,
                            AActor* DamageCauser);
    
    void RegisterKill(AController* KillerController);
    
    void CalculateAndApplyDamage(float Damage, AController* InstigatedBy);
    
    float GetPointDamageModifier(AActor* DamagedActor, const FName& BoneName);

    void ReportDamageEvent(const float Damage, AController* InstigatedBy) const;
};
