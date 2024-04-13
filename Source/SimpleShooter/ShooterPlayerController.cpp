// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"

#include "Blueprint/UserWidget.h"


void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	 HUDScreen = CreateWidget(this, HUDWidget);

	if (HUDScreen != nullptr)
	{
		HUDScreen->AddToViewport();
	}
}


void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	UE_LOG(LogTemp,Warning,TEXT("Gameover!"));
    HUDScreen->RemoveFromViewport();
	
	if (bIsWinner)
	{
		UUserWidget* WinnerScreen = CreateWidget(this, WinnerWidget);

		if (WinnerScreen != nullptr)
		{
			WinnerScreen->AddToViewport();
		}
	}

	else
	{
		UUserWidget* LoseScreen = CreateWidget(this, LoserWidget);

		if (LoseScreen != nullptr)
		{
			LoseScreen->AddToViewport();
		}
	}


	
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, Delay);
}
