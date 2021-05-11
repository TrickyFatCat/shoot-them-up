// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UTextRenderComponent;
class USTUHealthComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ASTUBaseCharacter(const FObjectInitializer& ObjInit);

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Camera
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Camera")
    ;
    float SprintInputYawScale = 0.5f;
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    UCameraComponent* CameraComponent = nullptr;
    UPROPERTY(VisibleAnywhere, BlueprintReadoNLY, Category="Components", meta=(AllowPrivateAccess="true"))
    USpringArmComponent* SpringArmComponent = nullptr;
private:
    float DefaultInputYawScale = 2.5f;
    void SetInputYawScale(const float NewYawScale) const;

    // Movement
public:
    UFUNCTION(BlueprintPure, Category="Movement")
    bool GetIsSprinting() const;
    UFUNCTION(BlueprintPure, Category="Movement")
    float GetCurrentVelocity() const { return GetVelocity().Size(); }

    UFUNCTION(BlueprintPure, Category="Movement")
    float GetMovementDirection() const;
private:
    bool bIsMovingForward = false;
    bool bSprintPressed = false;

    void MoveForward(const float AxisValue);
    void MoveRight(const float AxisValue);
    void StartSprinting();
    void StopSprinting();

    // Health and damage
public:
protected:
    UPROPERTY(EditDefaultsOnly, Category="Animation")
    UAnimMontage* DeathAnimMontage = nullptr;
private:
    const float DestroyTime = 5.f;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
    USTUHealthComponent* HealthComponent = nullptr;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
    UTextRenderComponent* HealthTextComponent = nullptr;
    void OnDeath();
};
