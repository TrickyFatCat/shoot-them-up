// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/STUBaseCharacter.h"
#include "STUAICharacter.generated.h"

class UBehaviorTree;
class UWidgetComponent;

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUAICharacter : public ASTUBaseCharacter
{
	GENERATED_BODY()

public:
	ASTUAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI")
	UBehaviorTree* BehaviorTreeAsset;

	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;
	virtual void OnDeath() override;
	virtual void OnHealthChanged(const float Health, const float DeltaHealth) override;
	virtual void OnShieldChanged(const float Shield, const float DeltaShield) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component")
	UWidgetComponent* HealthBarWidgetComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI")
	float HealthWidgetVisibilityDistance = 1000.f;

private:
	void SetHealthBarPercent() const;
	void UpdateHealthWidgetVisibility() const;
};
