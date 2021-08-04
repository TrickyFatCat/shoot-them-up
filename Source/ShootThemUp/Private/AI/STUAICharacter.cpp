// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "AI/STUAICharacter.h"
#include "AI/STUAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/STUAIWeaponComponent.h"
#include "BrainComponent.h"
#include "UI/STUHealthBarWidget.h"
#include "Components/WidgetComponent.h"
#include "Components/STUHealthComponent.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& ObjInit) : Super(
    ObjInit.SetDefaultSubobjectClass<USTUAIWeaponComponent>("WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = ASTUAIController::StaticClass();

    bUseControllerRotationYaw = false;

    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.f, 200.f, 0.f);
    }

    HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthBarWidgetComponent");
    HealthBarWidgetComponent->SetupAttachment(GetRootComponent());
    HealthBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    HealthBarWidgetComponent->SetDrawAtDesiredSize(true);
}

void ASTUAICharacter::BeginPlay()
{
    Super::BeginPlay();
    check(HealthBarWidgetComponent);
}

void ASTUAICharacter::OnDeath()
{
    Super::OnDeath();

    AAIController* CurrentController = Cast<AAIController>(Controller);

    if (CurrentController && CurrentController->BrainComponent)
    {
        CurrentController->BrainComponent->Cleanup();
    }
}

void ASTUAICharacter::OnHealthChanged(const float Health, const float DeltaHealth)
{
    Super::OnHealthChanged(Health, DeltaHealth);
    SetHealthBarPercent();
}

void ASTUAICharacter::OnShieldChanged(const float Shield, const float DeltaShield)
{
    Super::OnShieldChanged(Shield, DeltaShield);
    SetHealthBarPercent();
}

void ASTUAICharacter::SetHealthBarPercent() const
{
    USTUHealthBarWidget* HealthBarWidget = Cast<USTUHealthBarWidget>(HealthBarWidgetComponent->GetUserWidgetObject());

    if (!HealthBarWidget) return;

    HealthBarWidget->SetHealthAndShieldPercent(HealthComponent->GetNormalizedHealth(),
                                               HealthComponent->GetNormalizedShield());
}
