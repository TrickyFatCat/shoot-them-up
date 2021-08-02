// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Menu/STUMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USTUMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (ButtonStartGame)
    {
        ButtonStartGame->OnClicked.AddDynamic(this, &USTUMenuWidget::OnStartGame);
    }
}

void USTUMenuWidget::OnStartGame()
{
    const FName StartLevelName = "Test";
    UGameplayStatics::OpenLevel(this, StartLevelName);
}
