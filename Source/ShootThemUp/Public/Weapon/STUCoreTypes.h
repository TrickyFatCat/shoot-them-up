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
    int32 ClipSize = 20;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon", meta=(EditCondition="!bIsInfinite", ClampMin="0"))
    int32 ClipsNumber = 5;
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
