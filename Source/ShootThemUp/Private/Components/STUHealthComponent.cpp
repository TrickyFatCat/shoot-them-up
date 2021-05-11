// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Dev/STUFireDamageType.h"
#include "Dev/STUIceDamageType.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

USTUHealthComponent::USTUHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    Health = bCustomInitialHealth ? InitialHealth : MaxHealth;
    Shield = bCustomInitialShield ? InitialShield : MaxShield;

    AActor* ComponentOwner = GetOwner();

    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
    }
}

void USTUHealthComponent::OnTakeAnyDamage(AActor* DamageActor,
    float Damage,
    const class UDamageType* DamageType,
    class AController* InstigatedBy,
    AActor* DamageCauser)
{
    if (Shield <= 0.f)
    {
        Health -= Damage;
    }
    else
    {
        if (Shield >= Damage)
        {
            Shield -= Damage;
        }
        else
        {
            Damage -= Shield;
            Shield = 0.f;
            Health -= Damage;
        }
    }

    if (DamageType)
    {
        if (DamageType->IsA<USTUFireDamageType>())
        {
            UE_LOG(LogHealthComponent, Display, TEXT("SO HOT! IT'S A FIRE ATTACK!"));
        }
        else if (DamageType->IsA<USTUIceDamageType>())
        {
            UE_LOG(LogHealthComponent, Display, TEXT("SO COLD! IT'S AN ICE ATTACK!"));
        }
    }
}
