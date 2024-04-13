// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterKiledPawnAllGameMode.h"

#include "EngineUtils.h"
#include "ShooterAIController.h"
#include "ShooterPlayerController.h"

void AShooterKiledPawnAllGameMode::PawnKilled(APawn* PawnKilled) 
{
	Super::PawnKilled(PawnKilled);

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());

	if (PlayerController != nullptr)
	{
		EndGame(false);
	}

	for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
	{
		if (!Controller->IsDead())
		{
			return;
		}
		
	}
	EndGame(true);
	UE_LOG(LogTemp, Warning, TEXT("A pawn was killed!"));
}


void AShooterKiledPawnAllGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
		
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;

		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
		
	}
}

