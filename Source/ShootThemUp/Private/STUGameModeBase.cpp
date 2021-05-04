// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "STUGameModeBase.h"
#include "Characters/STUBaseCharacter.h"
#include "Characters/Controllers/STUPlayerController.h"

ASTUGameModeBase::ASTUGameModeBase()
{
    DefaultPawnClass = ASTUBaseCharacter::StaticClass();
    PlayerControllerClass = ASTUPlayerController::StaticClass();
}
