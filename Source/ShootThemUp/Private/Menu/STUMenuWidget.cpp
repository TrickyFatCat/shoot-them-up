// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Menu/STUMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STUGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogMenuWidget, All, All);

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
    UWorld* World = GetWorld();

    if (!World) return;

    USTUGameInstance* GameInstance = Cast<USTUGameInstance>(World->GetGameInstance());

    if (!GameInstance) return;

    const FName StartLevelName = GameInstance->GetStartLevelName();
    
    if (StartLevelName.IsNone())
    {
        UE_LOG(LogMenuWidget, Error, TEXT("Start level name is NONE") )
    }
    
    UGameplayStatics::OpenLevel(this, StartLevelName);
}
