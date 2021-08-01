// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "UI/STUGameOverWidget.h"
#include "STUGameModeBase.h"
#include "Characters/STUPlayerState.h"
#include "UI/STUPlayerStatRowWidget.h"
#include "Components/VerticalBox.h"
#include "STUUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void USTUGameOverWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    if (GetWorld())
    {
        ASTUGameModeBase* GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &USTUGameOverWidget::OnMatchStateChanged);
        }
    }

    if (ButtonResetLevel)
    {
        ButtonResetLevel->OnClicked.AddDynamic(this, &USTUGameOverWidget::OnResetLevel);
    }
}

void USTUGameOverWidget::OnMatchStateChanged(ESTUMatchState NewState)
{
    if (NewState == ESTUMatchState::GameOver)
    {
        UpdatePlayerStat();
    }
}

void USTUGameOverWidget::UpdatePlayerStat() const
{
    UWorld* World = GetWorld();

    if (!World || !PlayerStatBox) return;

    PlayerStatBox->ClearChildren();

    for (auto It = World->GetControllerIterator(); It; ++It)
    {
        AController* Controller = It->Get();

        if (!Controller) continue;

        ASTUPlayerState* PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);

        if (!PlayerState) continue;

        USTUPlayerStatRowWidget* PlayerStatRowWidget = CreateWidget<USTUPlayerStatRowWidget>(
            World,
            PlayerStatRowWidgetClass);

        if (!PlayerStatRowWidget) continue;

        PlayerStatRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
        PlayerStatRowWidget->SetKills(STUUtils::TextFromInt(PlayerState->GetKillsNumber()));
        PlayerStatRowWidget->SetDeaths(STUUtils::TextFromInt(PlayerState->GetDeathsNumber()));
        PlayerStatRowWidget->SetTeam(STUUtils::TextFromInt(PlayerState->GetTeamID()));
        PlayerStatRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());
        PlayerStatBox->AddChild(PlayerStatRowWidget);
    }
}

void USTUGameOverWidget::OnResetLevel()
{
    const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
    UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}
