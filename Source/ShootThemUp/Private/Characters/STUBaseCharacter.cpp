// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Characters/STUBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(GetRootComponent());
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
	PlayerInputComponent->BindAxis("MoveFroward", this, &ASTUBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);

	// Camera bindings
	PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::LookUp);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASTUBaseCharacter::TurnAround);
}

void ASTUBaseCharacter::LookUp(const float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void ASTUBaseCharacter::TurnAround(const float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void ASTUBaseCharacter::MoveForward(const float AxisValue)
{
	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void ASTUBaseCharacter::MoveRight(const float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue);
}

