// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Pickups/STUHealthPickup.h"


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

