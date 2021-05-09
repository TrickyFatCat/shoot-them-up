// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Dev/STUDevDamageActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ASTUDevDamageActor::ASTUDevDamageActor()
{
    PrimaryActorTick.bCanEverTick = true;
    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    SetRootComponent(SceneComponent);
}

void ASTUDevDamageActor::BeginPlay()
{
    Super::BeginPlay();
}

void ASTUDevDamageActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    const FVector ActorLocation = GetActorLocation();
    DrawDebugSphere(GetWorld(), ActorLocation, Radius, 24, SphereColor);
    UGameplayStatics::ApplyRadialDamage(GetWorld(),
                                        Damage,
                                        ActorLocation,
                                        Radius,
                                        DamageType,
                                        {},
                                        this,
                                        nullptr,
                                        bDoFullDamage);
}
