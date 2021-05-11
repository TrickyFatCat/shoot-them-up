// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

USTUHealthComponent::USTUHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    Health = bCustomInitialHealth ? InitialHealth : MaxHealth;
    OnHealthChanged.Broadcast(Health, 0.f);
    Shield = bCustomInitialShield ? InitialShield : MaxShield;
    OnShieldChanged.Broadcast(Shield, 0.f);

    AActor* ComponentOwner = GetOwner();

    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
    }
}

void USTUHealthComponent::DecreaseHealth(const float Amount)
{
    if (Amount <= 0.f || Health <= 0.f) return;
    
    Health = FMath::Max(Health - Amount, 0.f);
    OnHealthChanged.Broadcast(Health, -Amount);

    if (GetIsDead())
    {
        OnDeath.Broadcast();
    }
}

void USTUHealthComponent::DecreaseShield(const float Amount)
{
    if (Amount <= 0.f || Shield <= 0.f) return;
    
    Shield = FMath::Max(Shield - Amount, 0.f);
    OnShieldChanged.Broadcast(Shield, -Amount);
}

void USTUHealthComponent::OnTakeAnyDamage(AActor* DamageActor,
                                          float Damage,
                                          const class UDamageType* DamageType,
                                          class AController* InstigatedBy,
                                          AActor* DamageCauser)
{
    if (Damage <= 0.f || GetIsDead()) return;

    if (Shield <= 0.f)
    {
        DecreaseHealth(Damage);
    }
    else
    {
        if (Shield >= Damage)
        {
            DecreaseShield(Damage);
        }
        else
        {
            Damage -= Shield;
            DecreaseShield(Shield);
            DecreaseHealth(Damage);
        }
    }
}
