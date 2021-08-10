// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraShake.h"
#include "Objects/Resource.h"
#include "STUGameModeBase.h"
#include "STUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

USTUHealthComponent::USTUHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    HealthObject = NewObject<UResource>(this, TEXT("Health"));
    HealthObject->SetResourceData(HealthData);
    HealthObject->OnValueChanged.AddUObject(this, &USTUHealthComponent::BroadcastOnHealthChanged);
    ShieldObject = NewObject<UResource>(this, TEXT("Shield"));
    ShieldObject->OnValueChanged.AddUObject(this, &USTUHealthComponent::BroadcastOnShieldChanged);
    ShieldObject->SetResourceData(ShieldData);

    AActor* ComponentOwner = GetOwner();

    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
    }
}

void USTUHealthComponent::DecreaseHealth(const float DeltaHealth, AController* InstigatorController)
{
    if (InstigatorController)
    {
        const bool bIsInstigatorEnemey =
            STUUtils::AreEnemies(GetOwner()->GetInstigatorController(), InstigatorController);

        if (!bIsInstigatorEnemey) return;
    }

    if (DeltaHealth <= 0.f || GetHealth() <= 0.f) return;

    HealthObject->DecreaseValue(DeltaHealth);

    if (GetIsDead())
    {
        ShieldObject->SetAutoIncreaseEnabled(false);
        RegisterKill(InstigatorController);
        OnDeath.Broadcast();
    }
}

bool USTUHealthComponent::IncreaseHealth(const float DeltaHealth, const bool bClampToMax)
{
    if (DeltaHealth <= 0.f || GetHealth() <= 0.f) return false;

    HealthObject->IncreaseValue(DeltaHealth, bClampToMax);
    return true;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void USTUHealthComponent::BroadcastOnHealthChanged(const float CurrentHealth, const float DeltaHealth)
{
    OnHealthChanged.Broadcast(CurrentHealth, DeltaHealth);
}

void USTUHealthComponent::DecreaseShield(const float DeltaShield, AController* InstigatorController)
{
    if (InstigatorController)
    {
        const bool bIsInstigatorEnemey =
            STUUtils::AreEnemies(GetOwner()->GetInstigatorController(), InstigatorController);

        if (!bIsInstigatorEnemey) return;
    }

    if (DeltaShield <= 0.f || GetShield() <= 0.f) return;

    ShieldObject->DecreaseValue(DeltaShield);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void USTUHealthComponent::BroadcastOnShieldChanged(const float CurrentShield, const float DeltaShield)
{
    OnShieldChanged.Broadcast(CurrentShield, DeltaShield);
}

void USTUHealthComponent::PlayCameraShake() const
{
    if (!DamageCameraShake) return;

    APawn* Player = Cast<APawn>(GetOwner());

    if (!Player) return;

    APlayerController* Controller = Player->GetController<APlayerController>();

    if (!Controller || !Controller->PlayerCameraManager) return;

    Controller->PlayerCameraManager->StartCameraShake(DamageCameraShake);
}

void USTUHealthComponent::OnTakeAnyDamage(AActor* DamageActor,
                                          float Damage,
                                          const class UDamageType* DamageType,
                                          class AController* InstigatedBy,
                                          AActor* DamageCauser)
{
    if (Damage <= 0.f || GetIsDead()) return;

    const float CurrentShield = GetShield();

    if (CurrentShield <= 0.f)
    {
        DecreaseHealth(Damage, InstigatedBy);
        ShieldObject->StopAutoIncrease();
        ShieldObject->StartAutoIncrease();
    }
    else
    {
        if (CurrentShield >= Damage)
        {
            DecreaseShield(Damage, InstigatedBy);
        }
        else
        {
            Damage -= CurrentShield;
            DecreaseShield(CurrentShield, InstigatedBy);
            DecreaseHealth(Damage, InstigatedBy);
        }
    }

    PlayCameraShake();
}

void USTUHealthComponent::RegisterKill(AController* KillerController)
{
    if (!GetWorld()) return;

    ASTUGameModeBase* GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());

    if (!GameMode) return;

    APawn* VictimPawn = Cast<APawn>(GetOwner());
    AController* VictimController = VictimPawn ? VictimPawn->Controller : nullptr;
    GameMode->RegisterKill(KillerController, VictimController);
}
