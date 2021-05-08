// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USTUHealthComponent();
    UFUNCTION(BlueprintGetter)
    float GetHealth() const { return Health; }
    UFUNCTION(BlueprintGetter)
    float GetMaxHealth() const { return MaxHealth; }
    UFUNCTION(BlueprintGetter)
    float GetInitialHealth() const { return InitialHealth; }

protected:
    virtual void BeginPlay() override;
    UPROPERTY(BlueprintGetter=GetHealth, meta=(AllowPrivateAccess="true"))
    float Health = 0.f;
    UPROPERTY(EditDefaultsOnly,
        BlueprintGetter=GetMaxHealth,
        meta=(AllowPrivateAccess="true"))
    float MaxHealth = 100.f;
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
    bool bCustomInitialValue = false;
    UPROPERTY(EditAnywhere, BlueprintGetter=GetInitialHealth, meta=(AllowPrivateAccess="true", ClampMin="1.0", EditCondition="bCustomInitialValue"))
    float InitialHealth= 100.f;
};
