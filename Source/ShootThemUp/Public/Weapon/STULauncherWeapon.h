// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STULauncherWeapon.generated.h"

class ASTUProjectile;

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTULauncherWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()
public:
    virtual void StartFire() override;
    virtual void StopFire() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    TSubclassOf<ASTUProjectile> ProjectileClass = nullptr;
    virtual void MakeShot() override;
};
