// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.


#include "Menu/STUMenuHUD.h"
#include "UI/STUBaseWidget.h"

void ASTUMenuHUD::BeginPlay()
{
    Super::BeginPlay();

    if (MenuWidgetClass)
    {
        USTUBaseWidget* MenuWidget = CreateWidget<USTUBaseWidget>(GetWorld(), MenuWidgetClass);

        if (MenuWidget)
        {
            MenuWidget->AddToViewport();
            MenuWidget->Show();
        }
    }
}
