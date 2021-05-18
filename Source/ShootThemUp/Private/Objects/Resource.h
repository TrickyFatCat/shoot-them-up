// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Resource.generated.h"

USTRUCT(BlueprintType)
struct FResourceData
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY()
	float Value = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base Parameters", meta=(ClampMin="0.0"))
	float ValueMax = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base Parameters")
	bool bCustomInitialValue = false;
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category="Base Parameters",
		meta=(EditCondition="bCustomInitialValue", ClampMin="0.0"))
	float ValueInitial = 100.f;
	
	// AutoIncrease Data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AutoIncrease")
	bool bAutoIncreaseEnabled = false;
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category="AutoIncrease",
		meta=(EditCondition="bAutoIncreaseEnabled", ClampMin="0.0", ClampMax="1.0"))
	float AutoIncreaseThreshold = 1.f;
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category="AutoIncrease",
		meta=(EditCondition="bAutoIncreaseEnabled", ClampMin="0.0"))
	float AutoIncreaseDelay = 1.f;
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category="AutoIncrease",
		meta=(EditCondition="bAutoIncreaseEnabled", ClampMin="0.0"))
	float AutoIncreaseFrequency = 1.f;
	UPROPERTY()
	float AutoIncreaseTime = 1.f;
	UPROPERTY(EditAnywhere,
		BlueprintReadWrite,
		Category="AutoIncrease",
		meta=(EditCondition="bAutoIncreaseEnabled", ClampMin="0.0"))
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
	void SetResourceData(const FResourceData& NewResourceData);
	float GetValue() const { return ResourceData.Value; }
	void SetValue(const float NewValue);
	float GetValueMax() const { return ResourceData.ValueMax; }
	void SetValueMax(const float NewValue);
	float GetNormalizedValue() const { return ResourceData.Value / ResourceData.ValueMax; }
	void DecreaseValue(const float DeltaValue);
	void IncreaseValue(const float DeltaValue, const bool bClampToMax);
	void DecreaseValueMax(const float DeltaValue, const bool bClampValue);
	void IncreaseValueMax(const float DeltaValue, const bool bClampValue);
	void SetAutoIncreaseEnabled(const bool bIsEnabled, const bool bStopAutoIncrease = true);
	void SetAutoIncreaseFrequency(const float NewFrequency);
	FOnValueIncreased OnValueIncreased;
	FOnValueDecreased OnValueDecreased;
	FOnValueMaxChanged OnValueMaxChanged;

protected:
	FResourceData ResourceData;
	FTimerHandle AutoIncreaseHandle;
	void StartAutoIncreaseDelay();
	void StartAutoIncrease();
	void ProcessAutoIncrease();
	void StopTimer(FTimerHandle& TimerHandle) const;
};
