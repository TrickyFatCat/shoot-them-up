// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"


USTUWeaponFXComponent::USTUWeaponFXComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}


void USTUWeaponFXComponent::BeginPlay()
{
    Super::BeginPlay();
}


void USTUWeaponFXComponent::TickComponent(float DeltaTime,
                                          ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
    UNiagaraSystem* ImpactEffect = DefaultEffect;

    if (Hit.PhysMaterial.IsValid())
    {
        const UPhysicalMaterial* PhysMat = Hit.PhysMaterial.Get();

        if (EffectsMap.Contains(PhysMat))
        {
            ImpactEffect = EffectsMap[PhysMat];
        }
    }
    
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}

