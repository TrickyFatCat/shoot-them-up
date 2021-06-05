// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Pickups/STUAmmoPickup.h"


ASTUAmmoPickup::ASTUAmmoPickup()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ASTUAmmoPickup::BeginPlay()
{
    Super::BeginPlay();
    
}

void ASTUAmmoPickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

