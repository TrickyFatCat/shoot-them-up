// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Objects/Resource.h"
#include "STUHealthComponent.generated.h"

class UCameraShakeBase;

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
    void DecreaseHealth(const float DeltaHealth);
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
    void DecreaseShield(const float DeltaShield);
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
    void PlayCameraShake() const;
    UFUNCTION()
    void OnTakeAnyDamage(AActor* DamageActor,
                         float Damage,
                         const UDamageType* DamageType,
                         AController* InstigatedBy,
                         AActor* DamageCauser);
};
