// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STUAIController.generated.h"

class USTUAIPerceptionComponent;

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUAIController : public AAIController
{
    GENERATED_BODY()
public:
    ASTUAIController();
    
protected:
    virtual void Tick(float DeltaSeconds) override;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    USTUAIPerceptionComponent* STUAIPerceptionComponent = nullptr;
    virtual void OnPossess(APawn* InPawn) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    FName TargetEneemyKeyName = "EnemyActor";

private:
    AActor* GetTargetActor() const;
};
