// Fill out your copyright notice in the Description page of Project Settings.


#include "HardpointManager.h"
#include "Hardpoint.h"
#include "EnemySpawner.h"

// Sets default values
AHardpointManager::AHardpointManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_delayTimer = delayBetweenHardpoints;
	m_hasActive = false;
	m_checkpointsComplete = false;
}

AActor* AHardpointManager::GetRandomHardpoint()
{
	TArray<AActor*> temp;

	for (int i = 0; i < hardPoints.Num(); i++)
	{
		if (Cast<AHardpoint>(hardPoints[i]))
		{
			if (Cast<AHardpoint>(hardPoints[i])->GetIsUnlocked() == true && Cast<AHardpoint>(hardPoints[i])->GetCooldown() == 0)
			{
				temp.Add(hardPoints[i]);
			}
		}
	}

	AActor* hardpoint = nullptr;

	if (temp.Num() != 0)
	{
		int rand = FMath::RandRange(0, (temp.Num() - 1));

		hardpoint = temp[rand];
	}

	return hardpoint;
}

AActor* AHardpointManager::GetNextHardpoint()
{
	AActor* hardpoint = nullptr;

	if (Cast<AHardpoint>(hardPoints[m_checkpoint]))
	{
		hardpoint = hardPoints[m_checkpoint];

		if (hardpoint != nullptr)
		{
			m_checkpoint += 1;
		}
	}

	if (m_checkpoint >= finalCheckpoint)
	{
		EndCheckpoints();
	}

	return hardpoint;
}

void AHardpointManager::GenerateRandomEvent()
{
	int rand = FMath::RandRange(1, 4);

	switch (rand)
	{
		case 1:
			enemySpawner->GenerateHardpointEnemies(eventOne[0], eventOne[1], eventOne[2], eventOne[3]);
			break;
		case 2:
			enemySpawner->GenerateHardpointEnemies(eventTwo[0], eventTwo[1], eventTwo[2], eventTwo[3]);
			break;
		case 3:
			enemySpawner->GenerateHardpointEnemies(eventThree[0], eventThree[1], eventThree[2], eventThree[3]);
			break;
		case 4:
			enemySpawner->GenerateHardpointEnemies(eventFour[0], eventFour[1], eventFour[2], eventFour[3]);
			break;
	}
}

void AHardpointManager::EndCheckpoints()
{
	for (int i = 0; i < hardPoints.Num(); i++)
	{
		if (Cast<AHardpoint>(hardPoints[i]))
		{
			Cast<AHardpoint>(hardPoints[i])->SetCooldown(0);
		}
	}

	m_checkpointsComplete = true;
}

void AHardpointManager::SetActiveHardpoint()
{
	if (m_checkpointsComplete == false)
	{
		m_activeHardpoint = Cast<AHardpoint>(GetNextHardpoint());
	}
	else
	{
		m_activeHardpoint = Cast<AHardpoint>(GetRandomHardpoint());
	}

	if (m_activeHardpoint != nullptr)
	{
		m_activeHardpoint->SetIsAwake(true, this);
		m_hasActive = true;
	}
}

void AHardpointManager::ResetHardpoint()
{
	for (int i = 0; i < hardPoints.Num(); i++)
	{
		Cast<AHardpoint>(hardPoints[i])->ReduceCooldown();
	}

	if (m_checkpointsComplete == true)
	{
		int rand = FMath::RandRange(1, 100);

		if (rand <= m_keyChance)
		{
			m_activeHardpoint->SpawnBonus(key);
		}
		else
		{
			m_keyChance += keyChanceIncrement;
		}
	}
	else
	{
		if (m_checkpoint == 1 || m_checkpoint == 3)
		{
			m_activeHardpoint->SpawnBonus(key);
		}
	}

	m_activeHardpoint->SetCooldown(hardpointCooldown);
	m_activeHardpoint->SetIsStarted(false);

	m_hardpointsComplete += 1;
	m_delayTimer = 0;
	m_activeHardpoint = nullptr;
	m_hasActive = false;
}

int AHardpointManager::GetHardpointsComplete()
{
	return m_hardpointsComplete;
}

// Called when the game starts or when spawned
void AHardpointManager::BeginPlay()
{
	Super::BeginPlay();

	m_keyChance = baseKeyChance;
}

// Called every frame
void AHardpointManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_hasActive == false)
	{
		m_delayTimer += DeltaTime;

		if (m_delayTimer >= delayBetweenHardpoints)
		{
			SetActiveHardpoint();
		}
	}
	else
	{
		if (m_activeHardpoint != nullptr)
		{
			if (m_activeHardpoint->CheckIsAwake() == false)
			{
				ResetHardpoint();
			}
		}
	}
}

