// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "UI/STUGameHUD.h"
#include "Blueprint/UserWidget.h"

void ASTUGameHUD::DrawHUD()
{
}

void ASTUGameHUD::BeginPlay()
{
    Super::BeginPlay();

    UUserWidget* PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);

    if (PlayerHUDWidget)
    {
        PlayerHUDWidget->AddToViewport();
    }
}