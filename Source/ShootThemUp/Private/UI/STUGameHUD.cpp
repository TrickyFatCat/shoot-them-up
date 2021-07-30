// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "UI/STUGameHUD.h"
#include "Blueprint/UserWidget.h"
#include "STUGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGameHUD, All, All);

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

    if (GetWorld())
    {
        ASTUGameModeBase* GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &ASTUGameHUD::OnMatchStateChanged);
        }
    }
}

void ASTUGameHUD::OnMatchStateChanged(ESTUMatchState NewState)
{
    UE_LOG(LogSTUGameHUD, Display, TEXT("Match state was changed: %s"), *UEnum::GetValueAsString(NewState));
}
