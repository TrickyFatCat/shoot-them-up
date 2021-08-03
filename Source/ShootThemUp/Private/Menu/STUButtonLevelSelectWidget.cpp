// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Menu/STUButtonLevelSelectWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void USTUButtonLevelSelectWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (ButtonSelectLevel)
    {
        ButtonSelectLevel->OnClicked.AddDynamic(this, &USTUButtonLevelSelectWidget::OnSelectButtonClicked);
    }
}

void USTUButtonLevelSelectWidget::SetLevelData(const FLevelData& Data)
{
    LevelData = Data;

    if (TextLevelDisplayName)
    {
        TextLevelDisplayName->SetText(FText::FromName(Data.LevelDisplayName));
    }

    if (ImageLevelPicture)
    {
        ImageLevelPicture->SetBrushFromTexture(Data.LevelPicture);
    }

}

void USTUButtonLevelSelectWidget::SetSelected(bool bIsSelected)
{
    if (ImageFrame)
    {
        ImageFrame->SetVisibility(bIsSelected ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    }
}

void USTUButtonLevelSelectWidget::OnSelectButtonClicked()
{
    OnLevelSelected.Broadcast(LevelData);
}
