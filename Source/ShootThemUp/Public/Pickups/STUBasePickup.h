// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"

class USphereComponent;

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
    
protected:
    UPROPERTY(VisibleAnywhere, Category="Components")
    USphereComponent* CollisionComponent = nullptr;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup")
    float RespawnTime = 5.f;

    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
    virtual bool ActivateEffect(APawn* PlayerPawn);

private:
    void Hide();
    void Respawn() const;
};
