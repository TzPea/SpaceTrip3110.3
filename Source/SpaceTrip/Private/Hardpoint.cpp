// Fill out your copyright notice in the Description page of Project Settings.


#include "Hardpoint.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "HardpointManager.h"

// Sets default values
AHardpoint::AHardpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_cooldown = 0;
	m_timer = 0.0f;
	m_isUnlocked = false;
	m_isAwake = false;
	m_isActive = false;
}

bool AHardpoint::CheckForPlayer()
{
	if (m_player != nullptr)
	{
		FVector pLocation = m_player->GetActorLocation();
		FVector hLocation = GetActorLocation();

		float zCheck = pLocation.Z - hLocation.Z;

		if (zCheck > 400 || zCheck < -10)
		{
			return false;
		}

		hLocation.Z = 0.0f;	
		pLocation.Z = 0.0f;

		FVector distance = pLocation - hLocation;

		if (distance.Size() < radius)
		{
			return true;
		}
	}

	return false;
}

void AHardpoint::SetIsAwake(bool isawake, AHardpointManager* manager)
{
	m_manager = manager;
	m_isAwake = isawake;
}

bool AHardpoint::CheckIsAwake()
{
	return m_isAwake;
}

FString AHardpoint::GetName()
{
	return name;
}

void AHardpoint::CompleteHardpoint()
{
	TSubclassOf<AActor> reward = GenerateReward();

	FVector spawnLocation = GetActorLocation();
	spawnLocation.X += -100;
	spawnLocation.Z += 90;

	GetWorld()->SpawnActor<AActor>(reward, spawnLocation, GetActorRotation());

	m_timer = 0;
	m_isActive = false;
	m_isAwake = false;
}

int AHardpoint::GetCooldown()
{
	return m_cooldown;
}

void AHardpoint::SetCooldown(int cooldown)
{
	m_cooldown = cooldown;
}

void AHardpoint::ReduceCooldown()
{
	if (m_cooldown > 0)
	{
		m_cooldown -= 1;
	}
}

void AHardpoint::SetIsUnlocked(bool check)
{
	m_isUnlocked = check;
}

bool AHardpoint::GetIsUnlocked()
{
	return m_isUnlocked;
}

TSubclassOf<AActor> AHardpoint::GenerateReward()
{
	if (m_rewards.Num() != rewardRates.Num())
	{
		return nullptr;
	}

	int random = FMath::RandRange(1, 100);

	int lowRange;
	int highRange = 1;

	for (int i = 0; i < m_rewards.Num(); i++)
	{
		lowRange = highRange;
		highRange += rewardRates[i];

		if (random >= lowRange && random <= highRange)
		{
			return m_rewards[i];
		}
	}

	return nullptr;
}

void AHardpoint::SpawnBonus(TSubclassOf<AActor> bonus)
{
	FVector spawnLocation = GetActorLocation();
	spawnLocation.X += 100;
	spawnLocation.Z += 90;

	GetWorld()->SpawnActor<AActor>(bonus, spawnLocation, GetActorRotation());
}

float AHardpoint::GetTimer()
{
	return m_timer;
}

bool AHardpoint::GetIsActive()
{
	return m_isActive;
}

void AHardpoint::SetIsStarted(bool check)
{
	if (isStarted == false && check == true && m_manager != nullptr)
	{
		m_manager->GenerateRandomEvent();
	}

	isStarted = check;
}

// Called when the game starts or when spawned
void AHardpoint::BeginPlay()
{
	Super::BeginPlay();
	
	m_player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

// Called every frame
void AHardpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_isUnlocked == false)
	{
		return;
	}
	if (isStarted == false)
	{
		return;
	}

	if (m_isAwake == true)
	{
		m_isActive = CheckForPlayer();

		if (m_isActive == true)
		{
			m_timer += DeltaTime;

			if (m_timer > goalTime)
			{
				CompleteHardpoint();
			}
		}
		else
		{
			if (m_timer > 0.0f)
			{
				m_timer -= GetWorld()->DeltaTimeSeconds;

				if (m_timer < 0.0f)
				{
					m_timer = 0;
				}
			}
		}
	}
}

