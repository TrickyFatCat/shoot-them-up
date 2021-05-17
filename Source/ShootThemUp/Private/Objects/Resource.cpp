// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Resource.h"

#include "Math/UnitConversion.h"

void UResource::SetValue(const float NewValue)
{
	if (NewValue < 0.f || Value <= 0.f) return;

	Value = NewValue;
}

void UResource::SetValueMax(const float NewValue)
{
	if (NewValue <= 0.f) return;

	ValueMax = NewValue;
}

void UResource::DecreaseValue(const float DeltaValue, const bool bClampToZero)
{
	if (DeltaValue <= 0.f) return;

	Value -= DeltaValue;

	if (bClampToZero)
	{
		Value = FMath::Max(Value - DeltaValue, 0.f);
	}

	if (bAutoIncreaseEnabled)
	{
		StartAutoIncreaseDelay();
	}

	OnValueDecreased.Broadcast(Value);
}

void UResource::IncreaseValue(const float DeltaValue, const bool bClampToMax)
{
	if (DeltaValue <= 0.f) return;

	Value += DeltaValue;

	if (bClampToMax)
	{
		Value = FMath::Min(Value, ValueMax);
	}

	OnValueIncreased.Broadcast(Value);
}

void UResource::DecreaseValueMax(const float DeltaValue, const bool bClampValue)
{
	if (DeltaValue <= 0.f) return;

	ValueMax -= DeltaValue;

	if (bClampValue)
	{
		Value = FMath::Min(Value, ValueMax);
	}

	OnValueMaxChanged.Broadcast();
}

void UResource::IncreaseValueMax(const float DeltaValue, const bool bClampValue)
{
	if (DeltaValue <= 0.f)

		ValueMax += DeltaValue;

	if (bClampValue)
	{
		Value = ValueMax;
	}

	OnValueMaxChanged.Broadcast();
}

void UResource::SetupResource(const FResourceData ResourceData)
{
	Value = ResourceData.bCustomInitialValue ? ResourceData.ValueInitial : ResourceData.ValueMax;
	ValueMax = ResourceData.ValueMax;
	bAutoIncreaseEnabled = ResourceData.bAutoIncreaseEnabled;
	AutoIncreaseThreshold = ResourceData.AutoIncreaseThreshold;
	AutoIncreaseDelay = ResourceData.AutoIncreaseDelay;
	SetAutoIncreaseFrequency(ResourceData.AutoIncreaseFrequency);
	AutoIncreaseValue = ResourceData.AutoIncreaseValue;
}

void UResource::SetAutoIncreaseEnabled(const bool bIsEnabled, const bool bStopAutoIncrease)
{
	if (bAutoIncreaseEnabled == bIsEnabled) return;

	bAutoIncreaseEnabled = bIsEnabled;

	if (!bIsEnabled && bStopAutoIncrease)
	{
		UObject* Owner = GetOuter();

		if (!Owner) return;
		
		FTimerManager& TimerManager = Owner->GetWorld()->GetTimerManager();

		if (TimerManager.IsTimerActive(AutoIncreaseHandle))
		{
			TimerManager.ClearTimer(AutoIncreaseHandle);
		}
	}
}

void UResource::SetAutoIncreaseFrequency(const float NewFrequency)
{
	if (NewFrequency <= 0.f) return;

	AutoIncreaseFrequency = NewFrequency;
	AutoIncreaseTime = 1.f / NewFrequency;
}

void UResource::StartAutoIncreaseDelay()
{
	UObject* Owner = GetOuter();

	if (!Owner) return;

	FTimerManager& TimerManager = Owner->GetWorld()->GetTimerManager();

	if (TimerManager.IsTimerActive(AutoIncreaseHandle))
	{
		TimerManager.ClearTimer(AutoIncreaseHandle);
	}

	TimerManager.SetTimer(AutoIncreaseHandle,
	                      this,
	                      &UResource::StartAutoIncrease,
	                      AutoIncreaseDelay,
	                      false);
}

void UResource::StartAutoIncrease()
{
	UObject* Owner = GetOuter();

	if (!Owner) return;

	FTimerManager& TimerManager = Owner->GetWorld()->GetTimerManager();
	TimerManager.SetTimer(AutoIncreaseHandle, this, &UResource::ProcessAutoIncrease, AutoIncreaseTime, true);
}

void UResource::ProcessAutoIncrease()
{
	IncreaseValue(AutoIncreaseValue, false);

	if (Value / ValueMax >= AutoIncreaseThreshold)
	{
		UObject* Owner = GetOuter();

		if (!Owner) return;

		FTimerManager& TimerManager = Owner->GetWorld()->GetTimerManager();

		if (TimerManager.IsTimerActive(AutoIncreaseHandle))
		{
			TimerManager.ClearTimer(AutoIncreaseHandle);
		}
	}
}
