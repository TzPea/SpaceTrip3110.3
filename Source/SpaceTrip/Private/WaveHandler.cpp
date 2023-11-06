// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveHandler.h"

// Sets default values
AWaveHandler::AWaveHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_wave = 0;
	m_enemySpeedBonus = 0.0f;
}

void AWaveHandler::NextWave()
{
	if (m_wave == 0)
	{
		m_difIncreaseTimer = m_difIncreaseCooldown + 1;
	}

	m_wave += 1;
	m_difIncreaseTimer -= 1;

	if (m_difIncreaseTimer <= 0)
	{
		m_amountOfEnemies += m_amountOfEnemiesIncrement;
		m_enemySpeedBonus += m_enemySpeedBonusIncrement;
		m_difIncreaseTimer = m_difIncreaseCooldown;
	}

	if (m_wave == m_checkpointWaveOne)
	{
		m_spawnRates = m_spawnRatesOne;
	}
	else if (m_wave == m_checkpointWaveTwo)
	{
		m_spawnRates = m_spawnRatesTwo;
	}
	else if (m_wave == m_checkpointWaveThree)
	{
		m_spawnRates = m_spawnRatesThree;
	}
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

TArray<int> AWaveHandler::GetSpawnRates()
{
	return m_spawnRates;
}

// Called when the game starts or when spawned
void AWaveHandler::BeginPlay()
{
	Super::BeginPlay();

	m_spawnRates = m_baseSpawnRates;
}

// Called every frame
void AWaveHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

