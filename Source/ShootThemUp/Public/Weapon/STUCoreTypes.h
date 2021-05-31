#pragma once

#include "STUCoreTypes.generated.h"

class ASTUBaseWeapon;
// Only for weapon
DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature)

USTRUCT(BlueprintType)
struct FAmmoData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY()
    int32 ClipAmmo = 20;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon", meta=(ClampMin="0"))
    int32 ClipAmmoMax = 20;
    UPROPERTY()
    int32 InventoryAmmo = 100;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon", meta=(EditCondition="!bIsInfinite", ClampMin="0"))
    int32 InventoryAmmoMax = 100;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    bool bIsInfinite = false;
};

USTRUCT(BlueprintType)
struct FWeaponData
{
    GENERATED_USTRUCT_BODY()
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    TSubclassOf<ASTUBaseWeapon> WeaponClass;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    UAnimMontage* ReloadAnimMontage;
};
