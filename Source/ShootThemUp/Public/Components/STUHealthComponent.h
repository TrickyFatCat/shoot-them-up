// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Objects/Resource.h"
#include "STUHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnShieldChanged, float)

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
    UFUNCTION(BlueprintPure)
    bool GetIsDead() const { return GetHealth() <= 0.f; }
    FOnDeath OnDeath;
    FOnHealthChanged OnHealthChanged;
    void BroadcastOnHealthChanged(const float CurrentHealth);

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
    void BroadcastOnShieldChanged(const float CurrentShield);

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
    FResourceData ShieldData;
    UPROPERTY()
    UResource* ShieldObject = nullptr;
    
    // Damage
private:
    UFUNCTION()
    void OnTakeAnyDamage(AActor* DamageActor,
                         float Damage,
                         const UDamageType* DamageType,
                         AController* InstigatedBy,
                         AActor* DamageCauser);
};
