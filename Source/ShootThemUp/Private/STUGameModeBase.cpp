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
}

UClass* ASTUGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if(InController && InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }

    return AIPawnClass;
}

void ASTUGameModeBase::SpawnBots()
{
   if (!GetWorld()) return;

    for(int32 i = 0; i < GameData.PlayersNumber - 1; ++i)
    {
        FActorSpawnParameters SpawnInfo;
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        AAIController* STUAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
        RestartPlayer(STUAIController);
    }
}
