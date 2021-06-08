// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Weapon/STUProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Components/STUWeaponFXComponent.h"

ASTUProjectile::ASTUProjectile()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
    CollisionComponent->InitSphereRadius(5.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    SetRootComponent(CollisionComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
    MovementComponent->InitialSpeed = 2000.f;
    MovementComponent->ProjectileGravityScale = 0.f;

    WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

void ASTUProjectile::BeginPlay()
{
    Super::BeginPlay();

    check(MovementComponent);
    check(CollisionComponent);
    check(WeaponFXComponent);
    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
    CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
    CollisionComponent->OnComponentHit.AddDynamic(this, &ASTUProjectile::OnProjectileHit);
    SetLifeSpan(DefaultLifeSpan);
}

void ASTUProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent,
                                     AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp,
                                     FVector NormalImpulse,
                                     const FHitResult& Hit)
{
    UWorld* World = GetWorld();
    
    if (!World) return;

    MovementComponent->StopMovementImmediately();
    UGameplayStatics::ApplyRadialDamage(World,
                                        DamageAmount,
                                        GetActorLocation(),
                                        DamageRadius,
                                        UDamageType::StaticClass(),
                                        {GetOwner()},
                                        this,
                                        GetController(),
                                        bDoFullDamage);
    DrawDebugSphere(World, GetActorLocation(), DamageRadius, 24, FColor::Red, false, 5.f);
    WeaponFXComponent->PlayImpactFX(Hit);
    Destroy();
}

AController* ASTUProjectile::GetController() const
{
    const APawn* Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}
