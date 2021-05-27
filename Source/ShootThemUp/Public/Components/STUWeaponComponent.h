// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;
class ACharacter;
class UAnimMontage;
class USkeletalMeshComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USTUWeaponComponent();
    void StartFire();
    void StopFire();
    void EquipNextWeapon();
    void EquipPreviousWeapon();

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    UPROPERTY(EditDefaultsOnly, Category="Weapon")
    TArray<TSubclassOf<ASTUBaseWeapon>> WeaponClasses;
    UPROPERTY(EditDefaultsOnly, Category="Weapon")
    FName EquippedWeaponSocketName = "WeaponSocket";
    UPROPERTY(EditDefaultsOnly, Category="Weapon")
    FName ArmoryWeaponSocketName = "ArmorySocket";
    UPROPERTY(EditDefaultsOnly, Category="Animation")
    UAnimMontage* EquipAnimMontage = nullptr;

private:
    UPROPERTY()
    ACharacter* Owner = nullptr;
    UPROPERTY()
    ASTUBaseWeapon* CurrentWeapon = nullptr;
    UPROPERTY()
    TArray<ASTUBaseWeapon*> Weapons;
    int32 CurrentWeaponIndex = 0;
    bool bEquipInProgress = false;
    void SpawnWeapons();
    void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USkeletalMeshComponent* Mesh, const FName SocketName);
    void EquipWeapon(const int32 WeaponIndex);

    void PlayAnimMontage(UAnimMontage* Animation) const;
    void InitAnimations();
    void OnChangeWeapons(USkeletalMeshComponent* MeshComponent);
    void OnEquipFinished(USkeletalMeshComponent* MeshComponent);

    bool CanFire() const { return CurrentWeapon && !bEquipInProgress; }
    bool CanEquip() const { return !bEquipInProgress; }
};
