// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/STUCoreTypes.h"
#include "STUWeaponFXComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUWeaponFXComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USTUWeaponFXComponent();

protected:
    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime,
                               ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction) override;

public:
    void PlayImpactFX(const FHitResult& Hit);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
    FImpactData DefaultImpactData;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
    TMap<UPhysicalMaterial*, FImpactData> ImpactDataMap;
};
