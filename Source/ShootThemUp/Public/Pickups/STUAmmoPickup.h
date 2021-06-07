// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUBasePickup.h"
#include "STUAmmoPickup.generated.h"

class ASTUBaseWeapon;

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

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup", meta=(ClampMin="1.0"))
    int32 AmmoAmount = 20.0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup")
    TSubclassOf<ASTUBaseWeapon> WeaponType = nullptr;
    virtual bool ActivateEffect(APawn* PlayerPawn) override;
};
