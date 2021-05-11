// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Characters/STUBaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "Characters/Controllers/STUPlayerController.h"
#include "Components/InputComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/STUCharacterMovementComponent.h"
#include "Components/STUHealthComponent.h"

ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(
        ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");
    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
    HealthTextComponent->SetupAttachment(GetRootComponent());
}

void ASTUBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
    DefaultInputYawScale = Cast<ASTUPlayerController>(GetController())->InputYawScale;

    check(HealthComponent);
    check(HealthTextComponent);
    check(GetCharacterMovement());

    OnHealthChanged(HealthComponent->GetHealth(), 0.f);
    OnShieldChanged(HealthComponent->GetShield(), 0.f);
    HealthComponent->OnDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ASTUBaseCharacter::OnHealthChanged);
    HealthComponent->OnShieldChanged.AddUObject(this, &ASTUBaseCharacter::OnShieldChanged);
}

void ASTUBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Movement bindings
    PlayerInputComponent->BindAxis("MoveForward", this, &ASTUBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);

    // Camera bindings
    PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ASTUBaseCharacter::AddControllerYawInput);

    // Jump bindings
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUBaseCharacter::Jump);

    // Sprint bindings
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASTUBaseCharacter::StartSprinting);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASTUBaseCharacter::StopSprinting);
}

void ASTUBaseCharacter::SetInputYawScale(const float NewYawScale) const
{
    ASTUPlayerController* PlayerController = Cast<ASTUPlayerController>(GetController());

    if (PlayerController)
    {
        PlayerController->InputYawScale = NewYawScale;
    }
}

bool ASTUBaseCharacter::GetIsSprinting() const
{
    return bSprintPressed && bIsMovingForward && !GetVelocity().IsZero();
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

void ASTUBaseCharacter::MoveForward(const float AxisValue)
{
    bIsMovingForward = AxisValue > 0.f;

    if (AxisValue == 0.f) return;
    
    AddMovementInput(GetActorForwardVector(), AxisValue);

    SetInputYawScale(GetIsSprinting() ? SprintInputYawScale : DefaultInputYawScale);
}

void ASTUBaseCharacter::MoveRight(const float AxisValue)
{
    if (AxisValue == 0.f || GetIsSprinting()) return;
    
    AddMovementInput(GetActorRightVector(), AxisValue);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ASTUBaseCharacter::StartSprinting()
{
    bSprintPressed = true;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ASTUBaseCharacter::StopSprinting()
{
    bSprintPressed = false;
}

void ASTUBaseCharacter::OnDeath()
{
    PlayAnimMontage(DeathAnimMontage);

    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(DestroyTime);

    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
}

void ASTUBaseCharacter::OnHealthChanged(const float Health, const float DeltaHealth)
{
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void ASTUBaseCharacter::OnShieldChanged(const float Shield, const float DeltaShield)
{
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Shield)));
}