// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"

class USphereComponent;
class USoundCue;

UCLASS()
class SHOOTTHEMUP_API ASTUBasePickup : public AActor
{
    GENERATED_BODY()

public:
    ASTUBasePickup();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    bool GetIsActive() const { return bIsActive; };
    
protected:
    UPROPERTY(VisibleAnywhere, Category="Pickup")
    bool bIsActive;
    UPROPERTY(VisibleAnywhere, Category="Components")
    USphereComponent* CollisionComponent = nullptr;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup")
    float RespawnTime = 5.f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sound")
    USoundCue* PickupSound = nullptr;

    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
    virtual bool ActivateEffect(APawn* PlayerPawn);

private:
    float RotationYaw = 1.f;
    void Hide();
    void Respawn();
    void GenerateRotationYaw();
};
