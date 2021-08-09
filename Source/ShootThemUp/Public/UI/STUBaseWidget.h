// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUBaseWidget.generated.h"

class USoundCue;

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUBaseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    void Show();
    
protected:
    UPROPERTY(Transient, meta=(BindWidgetAnim))
    UWidgetAnimation* ShowAnimation = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sound")
    USoundCue* OpenSound;
};
