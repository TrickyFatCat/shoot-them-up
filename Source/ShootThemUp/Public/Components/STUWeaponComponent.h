// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/STUBaseWeapon.h"

#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;
class ACharacter;
class UAnimMontage;
class USkeletalMeshComponent;

USTRUCT(BlueprintType)
struct FWeaponData
{
    GENERATED_USTRUCT_BODY()
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    TSubclassOf<ASTUBaseWeapon> WeaponClass;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    UAnimMontage* ReloadAnimMontage;
};

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
    void Reload();

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
    
private:
    UPROPERTY()
    ACharacter* Owner = nullptr;
    UPROPERTY()
    ASTUBaseWeapon* CurrentWeapon = nullptr;
    UPROPERTY()
    TArray<ASTUBaseWeapon*> Weapons;
    int32 CurrentWeaponIndex = 0;
    bool bEquipInProgress = false;
    bool bReloadInProgress = false;
    void SpawnWeapons();
    void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USkeletalMeshComponent* Mesh, const FName SocketName);
    void EquipWeapon(const int32 WeaponIndex);

    void PlayAnimMontage(UAnimMontage* Animation) const;
    void InitAnimations();
    void OnChangeWeapons(USkeletalMeshComponent* MeshComponent);
    void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
    void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

    bool CanFire() const { return CurrentWeapon && !bEquipInProgress && !bReloadInProgress; }
    bool CanEquip() const { return !bEquipInProgress && !bReloadInProgress; }
    bool CanReload() const { return CurrentWeapon && !bEquipInProgress && !bReloadInProgress && CurrentWeapon->CanReload(); }

    void OnEmptyClip();
    void ReloadClip();
    
    template<typename T>
    T* FindFirstNotifyByClass(UAnimSequenceBase* Animation)
    {
        if (!Animation) return nullptr;

        const auto NotifyEvents = Animation->Notifies;

        for (auto NotifyEvent : NotifyEvents)
        {
            auto AnimNotify = Cast<T>(NotifyEvent.Notify);

            if (AnimNotify)
            {
                return AnimNotify;
            }
        }
        
        return nullptr;
    }
};
