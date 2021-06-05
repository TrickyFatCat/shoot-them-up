﻿// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUBasePickup.h"
#include "STUAmmoPickup.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUAmmoPickup : public ASTUBasePickup 
{
    GENERATED_BODY()

public:
    ASTUAmmoPickup();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
};
