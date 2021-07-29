// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Characters/STUPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/STUWeaponComponent.h"
#include "Characters/Controllers/STUPlayerController.h"

ASTUPlayerCharacter::ASTUPlayerCharacter(const FObjectInitializer& ObjInit) : Super(
    ObjInit)
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->SocketOffset = FVector(0.f, 75.f, 80.f);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);
}

void ASTUPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Movement bindings
    PlayerInputComponent->BindAxis("MoveForward", this, &ASTUPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASTUPlayerCharacter::MoveRight);

    // Camera bindings
    PlayerInputComponent->BindAxis("LookUp", this, &ASTUPlayerCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ASTUPlayerCharacter::AddControllerYawInput);

    // Jump bindings
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUPlayerCharacter::Jump);

    // Sprint bindings
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASTUPlayerCharacter::StartSprinting);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASTUPlayerCharacter::StopSprinting);

    // Weapon bindings
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTUWeaponComponent::StartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTUWeaponComponent::StopFire);
    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USTUWeaponComponent::EquipNextWeapon);
    PlayerInputComponent->BindAction("PreviousWeapon",
                                     IE_Pressed,
                                     WeaponComponent,
                                     &USTUWeaponComponent::EquipPreviousWeapon);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USTUWeaponComponent::Reload);
}

void ASTUPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    ASTUPlayerController* CurrentController = Cast<ASTUPlayerController>(GetController());

    if (CurrentController)
    {
        DefaultInputYawScale = CurrentController->InputYawScale;
    }
}

void ASTUPlayerCharacter::SetInputYawScale(const float NewYawScale) const
{
    ASTUPlayerController* PlayerController = Cast<ASTUPlayerController>(GetController());

    if (PlayerController)
    {
        PlayerController->InputYawScale = NewYawScale;
    }
}

bool ASTUPlayerCharacter::GetIsSprinting() const
{
    return bIsSprinting && bIsMovingForward && !GetVelocity().IsZero();
}

void ASTUPlayerCharacter::MoveForward(const float AxisValue)
{
    bIsMovingForward = AxisValue > 0.f;

    if (AxisValue == 0.f) return;

    AddMovementInput(GetActorForwardVector(), AxisValue);

    SetInputYawScale(GetIsSprinting() ? SprintInputYawScale : DefaultInputYawScale);
}

void ASTUPlayerCharacter::MoveRight(const float AxisValue)
{
    if (AxisValue == 0.f || GetIsSprinting()) return;

    AddMovementInput(GetActorRightVector(), AxisValue);
}

void ASTUPlayerCharacter::StartSprinting()
{
    Super::StartSprinting();
}

void ASTUPlayerCharacter::StopSprinting()
{
    Super::StopSprinting();
}

void ASTUPlayerCharacter::OnDeath()
{
    Super::OnDeath();
    
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
}
