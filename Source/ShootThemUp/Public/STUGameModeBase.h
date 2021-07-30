// A simple Shoot Them Up game made during UE4 C++ course. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "STUCoreTypes.h"
#include "STUGameModeBase.generated.h"

class AAIController;

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASTUGameModeBase();

	FOnMatchStateChangedSignature OnMatchStateChanged;

	virtual void StartPlay() override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	void RegisterKill(AController* KillerController, AController* VictimController);
	void RespawnRequest(AController* Controller);

	FGameData GetGameData() const { return GameData; }
	int32 GetCurrentRoundNum() const { return CurrentRound; }
	int32 GetRoundSecondsRemaining() const { return RoundCountDown; }
	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
	virtual bool ClearPause() override;
	bool IsMatchPaused() const { return CurrentMatchState == ESTUMatchState::Pause; }

protected:
	UPROPERTY(EditDefaultsOnly, Category="Game")
	TSubclassOf<AAIController> AIControllerClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Game")
	TSubclassOf<APawn> AIPawnClass = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category="Game")
	FGameData GameData;

private:
	ESTUMatchState CurrentMatchState = ESTUMatchState::Preparation;
	int32 CurrentRound = 1;
	int32 RoundCountDown = 0;
	FTimerHandle GameRoundTimerHandle;
	
	void SpawnBots();
	void StartRound();
	void UpdateRoundTimer();

	void ResetPlayers();
	void ResetOnePlayer(AController* Controller);

	void CreateTeams();
	FLinearColor DetermineTeamColor(int32 TeamID) const;
	void SetPlayerColor(AController* Controller);

	void ShowPlayersStatistics();

	void StartRespawn(AController* Controller);

	void GameOver();

	void SetMatchState(const ESTUMatchState NewState);
};
