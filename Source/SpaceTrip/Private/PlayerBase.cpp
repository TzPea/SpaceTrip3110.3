// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBase.h"

// Sets default values
APlayerBase::APlayerBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

FVector APlayerBase::GetPlayerVelocity()
{
	return GetVelocity();
}

void APlayerBase::CheckMovement()
{
	float moveCheck = GetVelocity().Length();

	if (moveCheck > 0.5f)
	{
		m_isMoving = true;
	}
	else
	{
		m_isMoving = false;
	}

	float fallCheck = GetVelocity().Z;

	if (0.5f < fallCheck || fallCheck < -0.5f)
	{
		m_isFalling = true;
	}
	else
	{
		m_isFalling = false;
	}
}

bool APlayerBase::GetIsMoving()
{
	return m_isMoving;
}

bool APlayerBase::GetIsFalling()
{
	return m_isFalling;
}

// Called when the game starts or when spawned
void APlayerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckMovement();

	if (m_health > 0)
	{
		m_timeAlive += DeltaTime;
	}
}

// Called to bind functionality to input
void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

