// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void GameHasEnded(AActor* EndGameFocus, bool bIsWinner) override;

private:
UPROPERTY(EditAnywhere)
	TSubclassOf<class  UUserWidget> LoserWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class  UUserWidget> WinnerWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class  UUserWidget> HUDWidget;

	UPROPERTY(EditAnywhere)
	float Delay = 5.f;

	FTimerHandle RestartTimer;

	UPROPERTY()
	UUserWidget* HUDScreen;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
};
