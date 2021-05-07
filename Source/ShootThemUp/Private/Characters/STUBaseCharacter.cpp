// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Characters/STUBaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/STUCharacterMovementComponent.h"

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(
        ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
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
