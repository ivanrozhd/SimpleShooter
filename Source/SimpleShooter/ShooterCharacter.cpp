// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

#include "Gun.h"
#include "ShooterGameMode.h"
#include "SimpleShooterGameMode.h"
#include "Components/CapsuleComponent.h"

class ASimpleShooterGameMode;
// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), PBO_None);
	//Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
    Gun->SetOwner(this);
	Health = MaxHealth;
	
}

bool AShooterCharacter::IsDead() const
{
	if (Health <= 0)
	{
		return true;
	}
	return false;
}

float AShooterCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AShooterCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &AShooterCharacter::Shoot);
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void AShooterCharacter::Shoot()
{
	Gun->PullTrigger();
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied =Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    DamageApplied = FMath::Min(Health, DamageApplied);
	Health -= DamageApplied;
	UE_LOG(LogTemp, Warning,TEXT("Health left %f"), Health);
    if (IsDead())
    {   AShooterGameMode* GameMode = GetWorld()->GetAuthGameMode<AShooterGameMode>();
    	if (GameMode != nullptr)
    	{
    		GameMode->PawnKilled(this);
    	}
	    DetachFromControllerPendingDestroy();
    	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    	

    }
	
	return  DamageApplied;
}


