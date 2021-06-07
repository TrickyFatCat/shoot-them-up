// A simple Shoot Them Up game made durign UE4 C++ course. All rights reserved.


#include "Pickups/STUHealthPickup.h"
#include "STUUtils.h"
#include "Components/STUHealthComponent.h"


ASTUHealthPickup::ASTUHealthPickup()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ASTUHealthPickup::BeginPlay()
{
    Super::BeginPlay();
}

void ASTUHealthPickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool ASTUHealthPickup::ActivateEffect(APawn* PlayerPawn)
{
    USTUHealthComponent* HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);

    if (!HealthComponent || HealthComponent->GetHealth() <= 0 || HealthComponent->GetHealth() >= HealthComponent->GetMaxHealth()) return false;

    return HealthComponent->IncreaseHealth(HealAmount, true);
}

