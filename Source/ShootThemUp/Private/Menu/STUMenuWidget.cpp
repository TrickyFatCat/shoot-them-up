// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Menu/STUMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "STUGameInstance.h"
#include "STUCoreTypes.h"
#include "Components/HorizontalBox.h"
#include "Menu/STUButtonLevelSelectWidget.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(LogMenuWidget, All, All);

void USTUMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (ButtonStartGame)
    {
        ButtonStartGame->OnClicked.AddDynamic(this, &USTUMenuWidget::OnStartGame);
    }

    if (ButtonQuitGame)
    {
        ButtonQuitGame->OnClicked.AddDynamic(this, &USTUMenuWidget::OnQuitGame);
    }

    InitLevelSelectButtons();
}

void USTUMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    if (Animation != HideAnimation) return;
    
    USTUGameInstance* GameInstance = GetGameInstance();

    if (!GameInstance) return;

    UGameplayStatics::OpenLevel(this, GameInstance->GetStartLevelData().LevelName);
}

void USTUMenuWidget::OnStartGame()
{
    PlayAnimation(HideAnimation);
    UGameplayStatics::PlaySound2D(GetWorld(), StartGameSound);
}

void USTUMenuWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void USTUMenuWidget::InitLevelSelectButtons()
{
    const USTUGameInstance* GameInstance = GetGameInstance();

    if (!GameInstance) return;

    checkf(GameInstance->GetLevelsData().Num() != 0, TEXT("Levels data must not be empty!"));

    if (!BoxLevelsSelectors) return;

    BoxLevelsSelectors->ClearChildren();

    for (auto LevelData : GameInstance->GetLevelsData())
    {
        USTUButtonLevelSelectWidget* LevelSelectButton = CreateWidget<USTUButtonLevelSelectWidget>(
            GetWorld(),
            SelectButtonWidgetClass);

        if (!LevelSelectButton) continue;

        LevelSelectButton->SetLevelData(LevelData);
        LevelSelectButton->OnLevelSelected.AddUObject(this, &USTUMenuWidget::OnLevelSelected);

        BoxLevelsSelectors->AddChild(LevelSelectButton);
        LevelSelectButtons.Add(LevelSelectButton);
    }

    if (GameInstance->GetStartLevelData().LevelName.IsNone())
    {
        OnLevelSelected(GameInstance->GetLevelsData()[0]);
    }
    else
    {
        OnLevelSelected(GameInstance->GetStartLevelData());
    }
}

void USTUMenuWidget::OnLevelSelected(const FLevelData& Data)
{
    USTUGameInstance* GameInstance = GetGameInstance();

    if (!GameInstance) return;

    GameInstance->SetStartLevelData(Data);

    for (auto LevelButton : LevelSelectButtons)
    {
        if (LevelButton)
        {
            const bool bIsSelected = Data.LevelName == LevelButton->GetLevelData().LevelName;
            LevelButton->SetSelected(bIsSelected);
        }
    }
}

USTUGameInstance* USTUMenuWidget::GetGameInstance() const
{
    UWorld* World = GetWorld();

    if (!World) return nullptr;

    return World->GetGameInstance<USTUGameInstance>();
}
