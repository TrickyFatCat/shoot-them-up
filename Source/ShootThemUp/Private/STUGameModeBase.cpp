// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "STUGameModeBase.h"
#include "Characters/STUBaseCharacter.h"
#include "Characters/Controllers/STUPlayerController.h"
#include "UI/STUGameHUD.h"
#include "STUCoreTypes.h"
#include "AIController.h"
#include "Characters/STUPlayerState.h"
#include "STUUtils.h"
#include "Components/STURespawnComponent.h"
#include "EngineUtils.h"

constexpr static int32 MinRoundTimeForRespawn = 10; // In seconds

ASTUGameModeBase::ASTUGameModeBase()
{
    DefaultPawnClass = ASTUBaseCharacter::StaticClass();
    PlayerControllerClass = ASTUPlayerController::StaticClass();
    HUDClass = ASTUGameHUD::StaticClass();
    PlayerStateClass = ASTUPlayerState::StaticClass();
}

void ASTUGameModeBase::StartPlay()
{
    Super::StartPlay();
    SpawnBots();
    CreateTeams();
    CurrentRound = 1;
    StartRound();
    SetMatchState(ESTUMatchState::Progress);
}

UClass* ASTUGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if (InController && InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }

    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ASTUGameModeBase::RegisterKill(AController* KillerController, AController* VictimController)
{
    ASTUPlayerState* KillerPlayerState = KillerController
                                             ? Cast<ASTUPlayerState>(KillerController->PlayerState)
                                             : nullptr;
    ASTUPlayerState* VictimPlayerState = VictimController
                                             ? Cast<ASTUPlayerState>(VictimController->PlayerState)
                                             : nullptr;

    if (KillerPlayerState)
    {
        KillerPlayerState->AddKill();
    }

    if (VictimPlayerState)
    {
        VictimPlayerState->AddDeath();
    }

    StartRespawn(VictimController);
}

void ASTUGameModeBase::RespawnRequest(AController* Controller)
{
    ResetOnePlayer(Controller);
}

bool ASTUGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
    const bool bIsPaused = Super::SetPause(PC, CanUnpauseDelegate);

    if (bIsPaused)
    {
        SetMatchState(ESTUMatchState::Pause);
    }

    return bIsPaused;
}

void ASTUGameModeBase::SpawnBots()
{
    if (!GetWorld()) return;

    for (int32 i = 0; i < GameData.PlayersNumber - 1; ++i)
    {
        FActorSpawnParameters SpawnInfo;
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        AAIController* STUAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
        RestartPlayer(STUAIController);
    }
}

void ASTUGameModeBase::StartRound()
{
    RoundCountDown = GameData.RoundDuration;
    GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &ASTUGameModeBase::UpdateRoundTimer, 1.0f, true);
}

void ASTUGameModeBase::UpdateRoundTimer()
{
    UE_LOG(LogTemp, Display, TEXT("Time: %i | Round: %i/%i"), RoundCountDown, CurrentRound, GameData.RoundsNumber);

    if (--RoundCountDown == 0)
    {
        GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

        if (CurrentRound + 1 <= GameData.RoundsNumber)
        {
            ++CurrentRound;
            ResetPlayers();
            StartRound();
        }
        else
        {
            GameOver();
        }
    }
}

void ASTUGameModeBase::ResetPlayers()
{
    if (!GetWorld()) return;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        ResetOnePlayer(It->Get());
    }
}

void ASTUGameModeBase::ResetOnePlayer(AController* Controller)
{
    if (Controller && Controller->GetPawn())
    {
        Controller->GetPawn()->Reset();
    }

    RestartPlayer(Controller);
    SetPlayerColor(Controller);
}

void ASTUGameModeBase::CreateTeams()
{
    if (!GetWorld()) return;

    int32 TeamID = 1;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        AController* Controller = It->Get();

        if (!Controller) continue;

        ASTUPlayerState* PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);

        if (!PlayerState) continue;

        PlayerState->SetTeamID(TeamID);
        PlayerState->SetTeamColor(DetermineTeamColor(TeamID));
        SetPlayerColor(Controller);

        TeamID = TeamID == 1 ? 2 : 1;
    }
}

FLinearColor ASTUGameModeBase::DetermineTeamColor(int32 TeamID) const
{
    if (TeamID - 1 < GameData.TeamColors.Num())
    {
        return GameData.TeamColors[TeamID - 1];
    }

    return GameData.DefaultTeamColor;
}

void ASTUGameModeBase::SetPlayerColor(AController* Controller)
{
    if (!Controller) return;

    ASTUBaseCharacter* Character = Cast<ASTUBaseCharacter>(Controller->GetPawn());

    if (!Character) return;

    ASTUPlayerState* PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);

    if (!PlayerState) return;

    Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void ASTUGameModeBase::ShowPlayersStatistics()
{
    if (!GetWorld()) return;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        AController* Controller = It->Get();

        if (!Controller) continue;

        ASTUPlayerState* PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);

        if (!PlayerState) continue;

        PlayerState->LogStatistics();
    }
}

void ASTUGameModeBase::StartRespawn(AController* Controller)
{
    const bool CanRespawned = RoundCountDown > MinRoundTimeForRespawn + GameData.RespawnTime;

    if (!CanRespawned) return;

    USTURespawnComponent* RespawnComponent = STUUtils::GetSTUPlayerComponent<USTURespawnComponent>(Controller);

    if (!RespawnComponent) return;

    RespawnComponent->StartRespawn(GameData.RespawnTime);
}

void ASTUGameModeBase::GameOver()
{
    for (auto Pawn : TActorRange<APawn>(GetWorld()))
    {
        if (Pawn)
        {
            Pawn->TurnOff();
            Pawn->DisableInput(nullptr);
        }
    }

    UE_LOG(LogTemp, Display, TEXT("===== GAME OVER ====="));
    ShowPlayersStatistics();
    SetMatchState(ESTUMatchState::GameOver);
}

void ASTUGameModeBase::SetMatchState(const ESTUMatchState NewState)
{
    if (CurrentMatchState == NewState) return;

    CurrentMatchState = NewState;
    OnMatchStateChanged.Broadcast(CurrentMatchState);
}
