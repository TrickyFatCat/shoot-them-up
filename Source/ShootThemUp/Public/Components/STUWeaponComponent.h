// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "Weapon/STUCoreTypes.h"
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
    virtual void StartFire();
    void StopFire();
    virtual void EquipNextWeapon();
    virtual void EquipPreviousWeapon();
    void Reload();
    bool GetWeaponUIData(FWeaponUIData& WeaponUIData) const;
    bool GetWeaponAmmoData(FAmmoData& AmmoData) const;
    bool IncreaseWeaponAmmo(TSubclassOf<ASTUBaseWeapon> WeaponType, int32 Amount);

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    UPROPERTY(EditDefaultsOnly, Category="Weapon")
    TArray<FWeaponData> WeaponData;
    UPROPERTY(EditDefaultsOnly, Category="Weapon")
    FName EquippedWeaponSocketName = "WeaponSocket";
    UPROPERTY(EditDefaultsOnly, Category="Weapon")
    FName ArmoryWeaponSocketName = "ArmorySocket";
    UPROPERTY(EditDefaultsOnly, Category="Animation")
    UAnimMontage* EquipAnimMontage = nullptr;
    UPROPERTY()
    UAnimMontage* CurrentReloadAnimMontage = nullptr;
    UPROPERTY()
    ASTUBaseWeapon* CurrentWeapon = nullptr;
    UPROPERTY()
    TArray<ASTUBaseWeapon*> Weapons;
    int32 CurrentWeaponIndex = 0;
    bool CanFire() const { return CurrentWeapon && !bEquipInProgress && !bReloadInProgress; }
    bool CanEquip() const { return !bEquipInProgress && !bReloadInProgress; }
    void EquipWeapon(const int32 WeaponIndex);
    bool bEquipInProgress = false;
    void PlayAnimMontage(UAnimMontage* Animation) const;
    
private:
    UPROPERTY()
    ACharacter* Owner = nullptr;
    bool bReloadInProgress = false;
    void SpawnWeapons();
    void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USkeletalMeshComponent* Mesh, const FName SocketName);

    void InitAnimations();
    void OnChangeWeapons(USkeletalMeshComponent* MeshComponent);
    void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
    void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

    bool CanReload() const
    {
        return CurrentWeapon && !bEquipInProgress && !bReloadInProgress && CurrentWeapon->CanReload();
    }

    void OnEmptyClip(ASTUBaseWeapon* WeaponToReload);
    void ReloadClip();
};
