// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ASTUBaseCharacter();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Camera
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    UCameraComponent* CameraComponent = nullptr;
    UPROPERTY(VisibleAnywhere, BlueprintReadoNLY, Category="Components", meta=(AllowPrivateAccess="true"))
    USpringArmComponent* SpringArmComponent = nullptr;

    // Movement
public:
    UFUNCTION(BlueprintGetter)
    float GetSprintSpeed() const { return SprintSpeed; }
    UFUNCTION(BlueprintSetter)
    void SetSprintSpeed(const float NewSpeed) { SprintSpeed = NewSpeed; }
private:
    UPROPERTY(EditDefaultsOnly,
        BlueprintReadWrite,
        BlueprintGetter=GetSprintSpeed,
        BlueprintSetter=SetSprintSpeed,
        Category="Movement",
        meta=(AllowPrivateAccess="true"))
    float SprintSpeed = 1000.f;
    float DefaultWalkSpeed = 600.f;
    void MoveForward(const float AxisValue);
    void MoveRight(const float AxisValue);
    void StartSprinting();
    void StopSprinting();
    void SetMaxWalkSpeed(const float NewSpeed) const;
};
