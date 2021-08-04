// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "UI/STUHealthBarWidget.h"
#include "Components/ProgressBar.h"

void USTUHealthBarWidget::SetHealthAndShieldPercent(const float HealthPercent, const float ShieldPercent)
{
    if (!ProgressBarHealth || !ProgressBarShield) return;

    ESlateVisibility NewVisibility = ESlateVisibility::Hidden;

    if (HealthPercent > HealthVisibilityThreshold && ShieldPercent < ShieldVisibilityThreshold)
    {
        NewVisibility = ESlateVisibility::Visible;
    }
    else if (HealthPercent < HealthVisibilityThreshold && HealthPercent > 0.f)
    {
        NewVisibility = ESlateVisibility::Visible;
    }

    ProgressBarHealth->SetVisibility(NewVisibility);
    ProgressBarShield->SetVisibility(NewVisibility);
    
    const FLinearColor HealthColor = HealthPercent > HealthColorThreshold ? HealthColorNormal : HealthColorCritical;
    ProgressBarHealth->SetFillColorAndOpacity(HealthColor);

    ProgressBarHealth->SetPercent(HealthPercent);
    ProgressBarShield->SetPercent(ShieldPercent);
}
