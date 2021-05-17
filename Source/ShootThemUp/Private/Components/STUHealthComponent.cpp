// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Objects/Resource.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

USTUHealthComponent::USTUHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

}

void USTUHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    HealthObject = NewObject<UResource>(this, TEXT("Health"));
    HealthObject->SetupResource(HealthData);
    HealthObject->OnValueIncreased.AddUObject(this, &USTUHealthComponent::BroadcastOnHealthChanged);
    HealthObject->OnValueDecreased.AddUObject(this, &USTUHealthComponent::BroadcastOnHealthChanged);
    ShieldObject = NewObject<UResource>(this, TEXT("Shield"));
    ShieldObject->OnValueIncreased.AddUObject(this, &USTUHealthComponent::BroadcastOnShieldChanged);
    ShieldObject->OnValueDecreased.AddUObject(this, &USTUHealthComponent::BroadcastOnShieldChanged);
    ShieldObject->SetupResource(ShieldData);

    AActor* ComponentOwner = GetOwner();

    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
    }

}

void USTUHealthComponent::DecreaseHealth(const float DeltaHealth)
{
    if (DeltaHealth <= 0.f || GetHealth() <= 0.f) return;
    
    HealthObject->DecreaseValue(DeltaHealth, true);

    if (GetIsDead())
    {
        ShieldObject->SetAutoIncreaseEnabled(false);
        OnDeath.Broadcast();
    }
}

void USTUHealthComponent::BroadcastOnHealthChanged(const float CurrentHealth)
{
    OnHealthChanged.Broadcast(CurrentHealth);
}

void USTUHealthComponent::DecreaseShield(const float DeltaShield)
{
    if (DeltaShield <= 0.f || GetShield()<= 0.f) return;
    
    ShieldObject->DecreaseValue(DeltaShield, true);
}

void USTUHealthComponent::BroadcastOnShieldChanged(const float CurrentShield)
{
    OnShieldChanged.Broadcast(CurrentShield);
}

void USTUHealthComponent::OnTakeAnyDamage(AActor* DamageActor,
                                          float Damage,
                                          const class UDamageType* DamageType,
                                          class AController* InstigatedBy,
                                          AActor* DamageCauser)
{
    if (Damage <= 0.f || GetIsDead()) return;

    const float CurrentShield = GetShield();

    if (CurrentShield <= 0.f)
    {
        DecreaseHealth(Damage);
    }
    else
    {
        if (CurrentShield >= Damage)
        {
            DecreaseShield(Damage);
        }
        else
        {
            Damage -= CurrentShield;
            DecreaseShield(CurrentShield);
            DecreaseHealth(Damage);
        }
    }
}
