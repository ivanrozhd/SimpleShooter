// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShooterGameMode.h"
#include "ShooterKiledPawnAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterKiledPawnAllGameMode : public AShooterGameMode
{
	GENERATED_BODY()
	
public:
	virtual void PawnKilled(APawn* PawnKilled) override;

private:
	void EndGame(bool bIsPlayerWinner);

	
};
