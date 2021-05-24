// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;
class ACharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USTUWeaponComponent();
    void StartFire();
    void StopFire();

protected:
    virtual void BeginPlay() override;
    UPROPERTY(EditDefaultsOnly, Category="Weapon")
    TSubclassOf<ASTUBaseWeapon> WeaponClass = nullptr;
    UPROPERTY(EditDefaultsOnly, Category="Weapon")
    FName WeaponSocketName = "WeaponSocket";
    void SpawnWeapon();

private:
    UPROPERTY()
    ACharacter* Owner = nullptr;
    UPROPERTY()
    ASTUBaseWeapon* CurrentWeapon = nullptr;
};
