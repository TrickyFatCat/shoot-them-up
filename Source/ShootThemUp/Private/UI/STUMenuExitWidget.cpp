// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "UI/STUMenuExitWidget.h"
#include "Components/Button.h"
#include "STUGameInstance.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogMenuExitWidget, All, All);

void USTUMenuExitWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (ButtonExitToMenu)
    {
        ButtonExitToMenu->OnClicked.AddDynamic(this, &USTUMenuExitWidget::OnExitToMenu);
    }
}

void USTUMenuExitWidget::OnExitToMenu()
{
    UWorld* World = GetWorld();

    if (!World) return;

    USTUGameInstance* GameInstance = World->GetGameInstance<USTUGameInstance>();

    if (!GameInstance) return;

    const FName MenuLevelName = GameInstance->GetMenuLevelName();

    if (MenuLevelName.IsNone())
    {
       UE_LOG(LogMenuExitWidget, Error, TEXT("Menu level name is none"));
       return;
    }
    
    UGameplayStatics::OpenLevel(this, MenuLevelName);
}