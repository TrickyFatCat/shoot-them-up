// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "AI/STUAICharacter.h"
#include "AI/STUAIController.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& ObjInit):Super(ObjInit)
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = ASTUAIController::StaticClass();
}
