// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveHandler.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWaveHandler::AWaveHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_wave = 0;
	m_incrementCooldown = 0;
	m_enemySpeedBonus = 0.0f;
	m_startIncrement = false;
}

void AWaveHandler::NextWave()
{
	if (m_wave == 0)
	{
		m_difIncreaseTimer = m_difIncreaseCooldown + 1;
	}

	m_wave += 1;
	m_difIncreaseTimer -= 1;
	m_miniBossCooldown -= 1;

	if (m_difIncreaseTimer <= 0)
	{
		m_amountOfEnemies += m_amountOfEnemiesIncrement;
		m_enemySpeedBonus += m_enemySpeedBonusIncrement;
		m_difIncreaseTimer = m_difIncreaseCooldown;
	}

	if (m_miniBossCooldown <= 0)
	{
		m_spawnMiniBoss = true;
		m_miniBossCooldown = m_miniBossDelay;
	}

	if (m_wave == m_checkpointWaveOne)
	{
		m_spawnRates = m_spawnRatesOne;
	}
	else if (m_wave == m_checkpointWaveTwo)
	{
		m_spawnRates = m_spawnRatesTwo;
	}
	else
	{
		if (m_startIncrement == false)
		{
			if (m_wave > m_checkpointWaveTwo)
			{
				m_startIncrement = true;
				m_incrementCooldown = m_incrementDelay;
			}

		}
		else
		{
			IncrementSpawnRates();
		}
	}

	//int rand = FMath::RandRange(0, (m_waveSounds.Num() - 1));

	//UGameplayStatics::PlaySoundAtLocation(m_waveSounds[rand],  GetActorLocation());
}

int AWaveHandler::GetWave()
{
	return m_wave;
}

float AWaveHandler::GetEnemySpeedBonus()
{
	return m_enemySpeedBonus;
}

int AWaveHandler::GetAmountOfEnemies()
{
	return m_amountOfEnemies;
}

void AWaveHandler::IncrementSpawnRates()
{
	if (m_spawnRates.Num() == m_spawnRateIncrement.Num() && m_incrementCooldown <= 0)
	{
		for (int i = 0; i < m_spawnRates.Num(); i++)
		{
			m_spawnRates[i] += m_spawnRateIncrement[i];
		}

		m_incrementCooldown = m_incrementDelay;
	}
}

TArray<int> AWaveHandler::GetSpawnRates()
{
	return m_spawnRates;
}

void AWaveHandler::SetMiniBossCheck(bool check)
{
	m_spawnMiniBoss = check;
}

bool AWaveHandler::SpawnMiniBossCheck()
{
	return m_spawnMiniBoss;
}

// Called when the game starts or when spawned
void AWaveHandler::BeginPlay()
{
	Super::BeginPlay();

	m_spawnRates = m_baseSpawnRates;
	m_spawnMiniBoss = false;
	m_miniBossCooldown = m_miniBossDelay;
}

// Called every frame
void AWaveHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

