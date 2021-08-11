// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Characters/Controllers/STUPlayerController.h"
#include "Components/STURespawnComponent.h"
#include "STUGameModeBase.h"
#include "STUGameInstance.h"

ASTUPlayerController::ASTUPlayerController()
{
    RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("STURespawnComponent");
}

void ASTUPlayerController::BeginPlay()
{
    if (GetWorld())
    {
        ASTUGameModeBase* GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &ASTUPlayerController::OnMatchStateChanged);
        }
    }
}

void ASTUPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    OnNewPawn.Broadcast(InPawn);
}

void ASTUPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (!InputComponent) return;

    FInputActionBinding& Pause = InputComponent->BindAction("PauseGame",
                                                            IE_Pressed,
                                                            this,
                                                            &ASTUPlayerController::OnPauseGame);
    Pause.bExecuteWhenPaused = true;
    InputComponent->BindAction("Mute", IE_Pressed, this, &ASTUPlayerController::OnMuteSound);
}

void ASTUPlayerController::OnPauseGame()
{
    if (!GetWorld()) return;

    ASTUGameModeBase* GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());

    if (!GameMode) return;

    if (!GameMode->IsMatchPaused())
    {
        GameMode->SetPause(this);
    }
    else
    {
        GameMode->ClearPause();
    }
}

void ASTUPlayerController::OnMatchStateChanged(ESTUMatchState NewState)
{
    if (NewState == ESTUMatchState::Progress)
    {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    }
    else
    {
        SetInputMode(FInputModeGameAndUI());
        bShowMouseCursor = true;
    }
}

void ASTUPlayerController::OnMuteSound()
{
    if (!GetWorld()) return;

    USTUGameInstance* GameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();

    if (!GameInstance) return;

    GameInstance->ToggleVolume();
}
