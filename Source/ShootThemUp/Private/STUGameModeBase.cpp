// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "STUGameModeBase.h"
#include "Characters/STUBaseCharacter.h"
#include "Characters/Controllers/STUPlayerController.h"
#include "UI/STUGameHUD.h"
#include "STUCoreTypes.h"
#include "AIController.h"

ASTUGameModeBase::ASTUGameModeBase()
{
    DefaultPawnClass = ASTUBaseCharacter::StaticClass();
    PlayerControllerClass = ASTUPlayerController::StaticClass();
    HUDClass = ASTUGameHUD::StaticClass();
}

void ASTUGameModeBase::StartPlay()
{
    Super::StartPlay();
    SpawnBots();
    CurrentRound = 1;
    StartRound();
}

UClass* ASTUGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if (InController && InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }

    return AIPawnClass;
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
            StartRound();
        }
        else
        {
            UE_LOG(LogTemp, Display, TEXT("===== GAME OVER ====="));
        }
    }
}

void ASTUGameModeBase::ResetPlayers()
{
    if (!GetWorld()) return;

    for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        ResetOnePlayer(It->Get());
    }
}

void ASTUGameModeBase::ResetOnePlayer(AController* Controller)
{
    if (Controller && Controller->GetPawn())
    {
        Controller->Reset();
    }
    
    RestartPlayer(Controller);
}
