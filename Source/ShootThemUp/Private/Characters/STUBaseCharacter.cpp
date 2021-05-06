// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Characters/STUBaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter()
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
	DefaultWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
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

void ASTUBaseCharacter::MoveForward(const float AxisValue)
{
	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void ASTUBaseCharacter::MoveRight(const float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ASTUBaseCharacter::StartSprinting()
{
	bIsSprinting = true;
	SetMaxWalkSpeed(SprintSpeed);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ASTUBaseCharacter::StopSprinting()
{
	bIsSprinting = false;
	SetMaxWalkSpeed(DefaultWalkSpeed);
}

void ASTUBaseCharacter::SetMaxWalkSpeed(const float NewSpeed) const
{
	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}

