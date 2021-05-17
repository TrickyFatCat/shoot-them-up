// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Resource.generated.h"

USTRUCT(BlueprintType)
struct FResourceData
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ValueMax = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCustomInitialValue = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bCustomInitialValue"))
	float ValueInitial = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAutoIncreaseEnabled = false;
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		meta=(EditCondition="bAutoIncreaseEnabled", ClampMin="0.0", ClampMax="1.0"))
	float AutoIncreaseThreshold = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bAutoIncreaseEnabled", ClampMin="0.0"))
	float AutoIncreaseDelay = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bAutoIncreaseEnabled", ClampMin="0.0"))
	float AutoIncreaseFrequency = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bAutoIncreaseEnabled", ClampMin="0.0"))
	float AutoIncreaseValue = 1.f;
};

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FOnValueIncreased, float)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnValueDecreased, float)
DECLARE_MULTICAST_DELEGATE(FOnValueMaxChanged);

UCLASS()
class SHOOTTHEMUP_API UResource : public UObject
{
	GENERATED_BODY()
public:
	float GetValue() const { return Value; }
	void SetValue(const float NewValue);
	float GetValueMax() const { return ValueMax; }
	void SetValueMax(const float NewValue);
	void DecreaseValue(const float DeltaValue, const bool bClampToZero);
	void IncreaseValue(const float DeltaValue, const bool bClampToMax);
	void DecreaseValueMax(const float DeltaValue, const bool bClampValue);
	void IncreaseValueMax(const float DeltaValue, const bool bClampValue);
	void SetupResource(const FResourceData ResourceData);
	void SetAutoIncreaseEnabled(const bool bIsEnabled, const bool bStopAutoIncrease = true);
	void SetAutoIncreaseFrequency(const float NewFrequency);
	FOnValueIncreased OnValueIncreased;
	FOnValueDecreased OnValueDecreased;
	FOnValueMaxChanged OnValueMaxChanged;

protected:
	float Value = 100.f;
	float ValueMax = 100.f;
	// Auto increase
	bool bAutoIncreaseEnabled = false;
	float AutoIncreaseThreshold = 1.f;
	float AutoIncreaseDelay = 3.f;
	float AutoIncreaseFrequency = 1.f;
	float AutoIncreaseTime = 1.f;
	float AutoIncreaseValue = 1.f;
	FTimerHandle AutoIncreaseHandle;
	void StartAutoIncreaseDelay();
	void StartAutoIncrease();
	void ProcessAutoIncrease();
};
