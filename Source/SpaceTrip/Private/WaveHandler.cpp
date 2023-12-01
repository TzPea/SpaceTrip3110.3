// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveHandler.h"
#include "EnemyBase.h"
#include "EnemySpawner.h"
#include "Sound/SoundWave.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWaveHandler::AWaveHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_spawnRates.Add(100);
	m_spawnRates.Add(0);
	m_spawnRates.Add(0);

	m_wave = 0;

	m_incrementCooldown = 0;
	m_enemySpeedBonus = 0.0f;
	m_startIncrement = false;
}

void AWaveHandler::NextWave()
{
	if (m_wave == 0)
	{
		m_difIncreaseTimer = difIncreaseCooldown + 1;
	}

	m_wave += 1;
	m_difIncreaseTimer -= 1;
	m_miniBossCooldown -= 1;

	if (m_difIncreaseTimer <= 0)
	{
		amountOfEnemiesBase += amountOfEnemiesIncrement;
		m_enemySpeedBonus += enemySpeedBonusIncrement;
		m_difIncreaseTimer = difIncreaseCooldown;
	}

	if (m_wave == waveToIntroduceStrawberries)
	{
		m_spawnRates[0] -= 10;
		m_spawnRates[1] += 10;
	}
	else if (m_wave == waveToIntroduceMelons)
	{
		m_spawnRates[0] -= 10;
		m_spawnRates[2] += 10;
	}
	else
	{
		if (m_startIncrement == false)
		{
			if (m_wave > waveToIntroduceMelons)
			{
				m_startIncrement = true;
				m_incrementCooldown = spawnRatesIncrementDelay;
			}

		}
		else
		{
			IncrementSpawnRates();
		}
	}

	if (m_wave == 1)
	{
		return;
	}

	int rand = FMath::RandRange(0, (waveSounds.Num() - 1));

	USoundWave* toPlay = waveSounds[rand];
	UGameplayStatics::PlaySoundAtLocation(this, toPlay, GetActorLocation());
}

int AWaveHandler::GetWave()
{
	return m_wave;
}

float AWaveHandler::GetEnemySpeedBonus()
{
	return m_enemySpeedBonus;
}

TArray<TSubclassOf<AActor>> AWaveHandler::GenerateWave()
{
	TArray<TSubclassOf<AActor>> temp;

	for (int i = 0; i < amountOfEnemiesBase; i++)
	{
		temp.Add(GenerateEnemy());
	}

	if (m_miniBossCooldown == 0)
	{
		m_miniBossCooldown = miniBossDelay;
		spawnerRef->QueueExtra(miniBoss);
	}

	return temp;
}
TSubclassOf<AActor> AWaveHandler::GenerateEnemy()
{
	float spawnRatesTotal = 0;
	TArray<float> trueSpawnRates;

	for (int i = 0; i < m_spawnRates.Num(); i++)
	{
		spawnRatesTotal += m_spawnRates[i];
	}

	for (int i = 0; i < m_spawnRates.Num(); i++)
	{
		float truePercent = (m_spawnRates[i] / spawnRatesTotal) * 100;
		trueSpawnRates.Add(truePercent);
	}


	float random = FMath::RandRange(1.0f, spawnRatesTotal);

	float lowRange;
	float highRange = 1;

	for (int i = 0; i < poolEnemies.Num(); i++)
	{
		lowRange = highRange;
		highRange += trueSpawnRates[i];

		if (random >= lowRange && random <= highRange)
		{
			return poolEnemies[i];
		}
	}

	return nullptr;
}

void AWaveHandler::IncrementSpawnRates()
{
	if (m_spawnRates.Num() == spawnRatesIncrement.Num() && m_incrementCooldown <= 0)
	{
		for (int i = 0; i < m_spawnRates.Num(); i++)
		{
			m_spawnRates[i] += spawnRatesIncrement[i];
		}

		m_incrementCooldown = spawnRatesIncrementDelay;
	}
}

// Called when the game starts or when spawned
void AWaveHandler::BeginPlay()
{
	Super::BeginPlay();

	m_spawnMiniBoss = false;
	m_miniBossCooldown = miniBossDelay;
}

// Called every frame
void AWaveHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

