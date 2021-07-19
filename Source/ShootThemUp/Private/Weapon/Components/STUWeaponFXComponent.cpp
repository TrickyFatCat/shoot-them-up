﻿// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "STUCoreTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"


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
    FImpactData ImpactData = DefaultImpactData;

    if (Hit.PhysMaterial.IsValid())
    {
        const UPhysicalMaterial* PhysMat = Hit.PhysMaterial.Get();

        if (ImpactDataMap.Contains(PhysMat))
        {
            ImpactData = ImpactDataMap[PhysMat];
        }
    }

    // Spawn niagara
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),
                                                   ImpactData.NiagaraEffect,
                                                   Hit.ImpactPoint,
                                                   Hit.ImpactNormal.Rotation());

    // Spawn decal
    UDecalComponent* DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),
                                                                             ImpactData.DecalData.Material,
                                                                             ImpactData.DecalData.Size,
                                                                             Hit.ImpactPoint,
                                                                             Hit.ImpactNormal.Rotation());

    if (DecalComponent)
    {
        DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutDuration);
    }
}
