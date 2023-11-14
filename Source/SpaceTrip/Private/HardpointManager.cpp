// Fill out your copyright notice in the Description page of Project Settings.


#include "HardpointManager.h"
#include "Hardpoint.h"

// Sets default values
AHardpointManager::AHardpointManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_delayTimer = m_hardpointDelay;
	m_hasActive = false;
	m_checkpointsComplete = false;
}

AActor* AHardpointManager::GetRandomHardpoint()
{
	TArray<AActor*> temp;

	for (int i = 0; i < m_hardPoints.Num(); i++)
	{
		if (Cast<AHardpoint>(m_hardPoints[i]))
		{
			if (Cast<AHardpoint>(m_hardPoints[i])->GetIsUnlocked() == true && Cast<AHardpoint>(m_hardPoints[i])->GetCooldown() == 0)
			{
				temp.Add(m_hardPoints[i]);
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

	if (Cast<AHardpoint>(m_hardPoints[m_checkpoint]))
	{
		hardpoint = m_hardPoints[m_checkpoint];

		if (hardpoint != nullptr)
		{
			m_checkpoint += 1;
		}
	}

	if (m_checkpoint >= m_finalCheckpoint)
	{
		EndCheckpoints();
	}

	return hardpoint;
}

void AHardpointManager::EndCheckpoints()
{
	for (int i = 0; i < m_hardPoints.Num(); i++)
	{
		if (Cast<AHardpoint>(m_hardPoints[i]))
		{
			Cast<AHardpoint>(m_hardPoints[i])->SetCooldown(0);
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
		m_activeHardpoint->SetIsAwake(true);
		m_hasActive = true;
	}
}

void AHardpointManager::ResetHardpoint()
{
	for (int i = 0; i < m_hardPoints.Num(); i++)
	{
		Cast<AHardpoint>(m_hardPoints[i])->ReduceCooldown();
	}

	if (m_checkpointsComplete == true)
	{
		int rand = FMath::RandRange(1, 100);

		if (rand <= m_keyChance)
		{
			m_activeHardpoint->SpawnBonus(m_key);
		}
		else
		{
			m_keyChance += m_keyChanceIncrement;
		}
	}
	else
	{
		if (m_checkpoint == 1 || m_checkpoint == 3)
		{
			m_activeHardpoint->SpawnBonus(m_key);
		}
	}

	m_activeHardpoint->SetCooldown(m_hardpointCooldown);

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

	m_keyChance = m_baseKeyChance;
}

// Called every frame
void AHardpointManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_hasActive == false)
	{
		m_delayTimer += DeltaTime;

		if (m_delayTimer >= m_hardpointDelay)
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

