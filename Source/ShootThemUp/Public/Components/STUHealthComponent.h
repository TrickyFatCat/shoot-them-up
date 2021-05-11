// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)

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
    UFUNCTION(BlueprintGetter)
    float GetHealth() const { return Health; }

    UFUNCTION(BlueprintGetter)
    float GetMaxHealth() const { return MaxHealth; }

    UFUNCTION(BlueprintGetter)
    float GetInitialHealth() const { return InitialHealth; }
    UFUNCTION(BlueprintCallable, Category="Health")
    void DecreaseHealth(const float Amount);
    UFUNCTION(BlueprintPure)
    bool GetIsDead() const { return Health <= 0.f; }
    FOnDeath OnDeath;

private:
    UPROPERTY(BlueprintGetter=GetHealth, Category="Health", meta=(AllowPrivateAccess="true"))
    float Health = 0.f;
    UPROPERTY(EditDefaultsOnly, BlueprintGetter=GetMaxHealth, Category="Health", meta=(AllowPrivateAccess="true"))
    float MaxHealth = 100.f;
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
    bool bCustomInitialHealth = false;
    UPROPERTY(EditAnywhere,
        BlueprintGetter=GetInitialHealth,
        Category="Health",
        meta=(AllowPrivateAccess="true", ClampMin="1.0", EditCondition="bCustomInitialHealth"))
    float InitialHealth = 100.f;

    // Shield 
public:
    UFUNCTION(BlueprintGetter)
    float GetShield() const { return Shield; }

    UFUNCTION(BlueprintGetter)
    float GetMaxShield() const { return MaxShield; }

    UFUNCTION(BlueprintGetter)
    float GetInitialShield() const { return InitialShield; }

    UFUNCTION(BlueprintCallable, Category="Shield")
    void DecreaseShield(const float Amount);

private:
    UPROPERTY(BlueprintGetter=GetShield, Category="Shield", meta=(AllowPrivateAccess="true"))
    float Shield = 0.f;
    UPROPERTY(EditDefaultsOnly, BlueprintGetter=GetMaxShield, Category="Shield", meta=(AllowPrivateAccess="true"))
    float MaxShield = 100.f;
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
    bool bCustomInitialShield = false;
    UPROPERTY(EditAnywhere, BlueprintGetter=GetInitialShield, Category="Shield", meta=(AllowPrivateAccess="true", ClampMin="0.0", EditCondition="bCustomInitialShield"))
    float InitialShield = 100.f;

    // Damage
private:
    UFUNCTION()
    void OnTakeAnyDamage(AActor* DamageActor,
                         float Damage,
                         const UDamageType* DamageType,
                         AController* InstigatedBy,
                         AActor* DamageCauser);
};
