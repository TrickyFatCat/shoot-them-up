// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/STUBaseCharacter.h"
#include "STUPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USphereComponent;

DECLARE_DELEGATE_OneParam(FZoomInputSignature, bool)
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUPlayerCharacter : public ASTUBaseCharacter
{
    GENERATED_BODY()
public:
    ASTUPlayerCharacter(const FObjectInitializer& ObjInit);
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
    virtual void BeginPlay() override;

    // Camera
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Camera")
    float SprintInputYawScale = 0.5f;
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    USphereComponent* CameraCollisionComponent = nullptr;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    UCameraComponent* CameraComponent = nullptr;
    UPROPERTY(VisibleAnywhere, BlueprintReadoNLY, Category="Components", meta=(AllowPrivateAccess="true"))
    USpringArmComponent* SpringArmComponent = nullptr;
private:
    float DefaultInputYawScale = 2.5f;
    void SetInputYawScale(const float NewYawScale) const;
    UFUNCTION()
    void OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                       AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp,
                                       int32 OtherBodyIndex,
                                       bool bFromSweep,
                                       const FHitResult& SweepResult);
    UFUNCTION()
    void OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent,
                                     AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp,
                                     int32 OtherBodyIndex);

    void CheckCameraOverlap();

    // Movement
public:
    virtual bool GetIsSprinting() const override;
protected:
    void MoveForward(const float AxisValue);
    void MoveRight(const float AxisValue);
    virtual void StartSprinting() override;
    virtual void StopSprinting() override;

    // Health and damage
protected:
    virtual void OnDeath() override;
};
