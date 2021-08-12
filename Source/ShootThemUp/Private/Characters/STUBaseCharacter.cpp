// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


// ReSharper disable CppMemberFunctionMayBeConst
#include "Characters/STUBaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Components/STUCharacterMovementComponent.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(
        ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = true;

    HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");
    WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("WeaponComponent");
}

void ASTUBaseCharacter::BeginPlay()
{
    Super::BeginPlay();


    check(HealthComponent);
    check(GetCharacterMovement());

    OnHealthChanged(HealthComponent->GetHealth(), 0.f);
    OnShieldChanged(HealthComponent->GetShield(), 0.f);
    HealthComponent->OnDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ASTUBaseCharacter::OnHealthChanged);
    HealthComponent->OnShieldChanged.AddUObject(this, &ASTUBaseCharacter::OnShieldChanged);

    LandedDelegate.AddDynamic(this, &ASTUBaseCharacter::OnGroundLanded);
}

void ASTUBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ASTUBaseCharacter::SetPlayerColor(const FLinearColor& TeamColor)
{
    UMaterialInstanceDynamic* MaterialInstance = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);

    if (!MaterialInstance) return;

    MaterialInstance->SetVectorParameterValue(MaterialColorName, TeamColor);
}

bool ASTUBaseCharacter::GetIsSprinting() const
{
    return false;
}

float ASTUBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero()) return 0.f;

    const FVector NormalizedVelocity = GetVelocity().GetSafeNormal();
    const FVector ForwardVector = GetActorForwardVector();
    const float AngleBetween = FMath::Acos(FVector::DotProduct(ForwardVector, NormalizedVelocity));
    const FVector CrossProduct = FVector::CrossProduct(ForwardVector, NormalizedVelocity);
    const float Degrees = FMath::RadiansToDegrees(AngleBetween);
    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ASTUBaseCharacter::StartSprinting()
{
    bIsSprinting = true;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ASTUBaseCharacter::StopSprinting()
{
    bIsSprinting = false;
}

void ASTUBaseCharacter::OnDeath()
{
    if (GetCurrentVelocity() != 0)
    {
        GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        GetMesh()->SetSimulatePhysics(true);
    }
    else
    {
        PlayAnimMontage(DeathAnimMontage);
    }

    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(DestroyTime);

    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    WeaponComponent->StopFire();
    WeaponComponent->SetZoom(false);
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ASTUBaseCharacter::OnHealthChanged(const float Health, const float DeltaHealth)
{
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ASTUBaseCharacter::OnShieldChanged(const float Shield, const float DeltaShield)
{
}

void ASTUBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
    const float FallVelocityZ = FMath::Abs(GetCharacterMovement()->Velocity.Z);

    if (FallVelocityZ < LandedDamageVelocity.X) return;

    const float FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);

    TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}
