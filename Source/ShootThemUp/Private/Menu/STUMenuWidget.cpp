// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Menu/STUMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "STUGameInstance.h"

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
}

void USTUMenuWidget::OnStartGame()
{
    UWorld* World = GetWorld();

    if (!World) return;

    USTUGameInstance* GameInstance = World->GetGameInstance<USTUGameInstance>();

    if (!GameInstance) return;

    const FName StartLevelName = GameInstance->GetStartLevelName();
    
    if (StartLevelName.IsNone())
    {
        UE_LOG(LogMenuWidget, Error, TEXT("Start level name is NONE") )
    }
    
    UGameplayStatics::OpenLevel(this, StartLevelName);
}

void USTUMenuWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
