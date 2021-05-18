// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Resource.h"

void UResource::SetResourceData(const FResourceData& NewResourceData)
{
	ResourceData = NewResourceData;
	ResourceData.Value = ResourceData.bCustomInitialValue ? ResourceData.ValueInitial : ResourceData.ValueMax;
	ResourceData.AutoIncreaseTime = 1 / ResourceData.AutoIncreaseFrequency;
}

void UResource::SetValue(const float NewValue)
{
	if (NewValue < 0.f || ResourceData.Value <= 0.f) return;

	ResourceData.Value = NewValue;
}

void UResource::SetValueMax(const float NewValue)
{
	if (NewValue <= 0.f) return;

	ResourceData.ValueMax = NewValue;
}

void UResource::DecreaseValue(const float DeltaValue)
{
	if (DeltaValue <= 0.f) return;

	ResourceData.Value = FMath::Max(ResourceData.Value - DeltaValue, 0.f);

	if (ResourceData.bAutoIncreaseEnabled && GetNormalizedValue() < ResourceData.AutoIncreaseThreshold)
	{
		if (ResourceData.AutoIncreaseDelay > 0.f)
		{
			StartAutoIncreaseDelay();
		}
		else
		{
			StartAutoIncrease();
		}
	}

	OnValueDecreased.Broadcast(ResourceData.Value);
}

void UResource::IncreaseValue(const float DeltaValue, const bool bClampToMax)
{
	if (DeltaValue <= 0.f) return;

	ResourceData.Value += DeltaValue;

	if (bClampToMax)
	{
		ResourceData.Value = FMath::Min(ResourceData.Value, ResourceData.ValueMax);
	}

	OnValueIncreased.Broadcast(ResourceData.Value);
}

void UResource::DecreaseValueMax(const float DeltaValue, const bool bClampValue)
{
	if (DeltaValue <= 0.f) return;

	ResourceData.ValueMax -= DeltaValue;

	if (bClampValue)
	{
		ResourceData.Value = FMath::Min(ResourceData.Value, ResourceData.ValueMax);
	}

	OnValueMaxChanged.Broadcast();
}

void UResource::IncreaseValueMax(const float DeltaValue, const bool bClampValue)
{
	if (DeltaValue <= 0.f)

		ResourceData.ValueMax += DeltaValue;

	if (bClampValue)
	{
		ResourceData.Value = ResourceData.ValueMax;
	}

	OnValueMaxChanged.Broadcast();
}

void UResource::SetAutoIncreaseEnabled(const bool bIsEnabled, const bool bStopAutoIncrease)
{
	if (ResourceData.bAutoIncreaseEnabled == bIsEnabled) return;

	ResourceData.bAutoIncreaseEnabled = bIsEnabled;

	if (!bIsEnabled && bStopAutoIncrease)
	{
		StopTimer(AutoIncreaseHandle);
	}
}

void UResource::SetAutoIncreaseFrequency(const float NewFrequency)
{
	if (NewFrequency <= 0.f) return;

	ResourceData.AutoIncreaseFrequency = NewFrequency;
	ResourceData.AutoIncreaseTime = 1.f / NewFrequency;
}

void UResource::StartAutoIncreaseDelay()
{
	StopTimer(AutoIncreaseHandle);
	GetWorld()->GetTimerManager().SetTimer(AutoIncreaseHandle,
	                                       this,
	                                       &UResource::StartAutoIncrease,
	                                       ResourceData.AutoIncreaseDelay,
	                                       false);
}

void UResource::StartAutoIncrease()
{
	StopTimer(AutoIncreaseHandle);
	GetWorld()->GetTimerManager().SetTimer(AutoIncreaseHandle,
	                                       this,
	                                       &UResource::ProcessAutoIncrease,
	                                       ResourceData.AutoIncreaseTime,
	                                       true);
}

void UResource::ProcessAutoIncrease()
{
	IncreaseValue(ResourceData.AutoIncreaseValue, false);

	if (ResourceData.Value / ResourceData.ValueMax >= ResourceData.AutoIncreaseThreshold)
	{
		StopTimer(AutoIncreaseHandle);
	}
}

void UResource::StopTimer(FTimerHandle& TimerHandle) const
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	if (TimerManager.IsTimerActive(TimerHandle))
	{
		TimerManager.ClearTimer(TimerHandle);
	}
}
