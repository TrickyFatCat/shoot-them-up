// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/STUBaseCharacter.h"
#include "STUPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

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
    UCameraComponent* CameraComponent = nullptr;
    UPROPERTY(VisibleAnywhere, BlueprintReadoNLY, Category="Components", meta=(AllowPrivateAccess="true"))
    USpringArmComponent* SpringArmComponent = nullptr;
private:
    float DefaultInputYawScale = 2.5f;
    void SetInputYawScale(const float NewYawScale) const;

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
