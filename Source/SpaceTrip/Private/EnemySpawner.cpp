// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySpawner.h"
#include "SpawnPoint.h"
#include "EnemyPool.h"
#include "WaveHandler.h"
#include "EnemyBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_toSpawn = 0;
	m_spawnDelay = 4.0f;
	m_spawnTimer = 0.0f;
	m_spawnMiniBoss = false;
	m_enemiesAlive = 0;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	NewWave();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnPoint::StaticClass(), m_spawnPoints);

	if (m_spawnPoints.Num() != 0)
	{
		for (int i = 0; i < m_spawnPoints.Num(); i++)
		{
			ASpawnPoint* temp = Cast<ASpawnPoint>(m_spawnPoints[i]);

			if (temp != nullptr)
			{
				temp->SetSpawnPoint(m_minDistance, m_maxDistance, m_zAxisCheck, m_spawnpointDelay);
			}
		}
	}
}

TSubclassOf<AActor> AEnemySpawner::GenerateToSpawn()
{

	m_spawnRates = m_waveRef->GetSpawnRates();

	if (m_poolEnemies.Num() != m_spawnRates.Num())
	{
		return nullptr;
	}

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


	float random  = FMath::RandRange(1.0f, spawnRatesTotal);

	float lowRange;
	float highRange = 1;

	for (int i = 0; i < m_poolEnemies.Num(); i++)
	{
		lowRange = highRange;
		highRange += trueSpawnRates[i];

		if (random >= lowRange && random <= highRange)
		{
			return m_poolEnemies[i];
		}
	}

	return nullptr;
}

void AEnemySpawner::SpawnEnemy()
{
	if (m_spawnPoints.Num() != 0)
	{
		TArray<AActor*> activeSpawnPoints;

		for (int i = 0; i < m_spawnPoints.Num(); i++)
		{
			ASpawnPoint* temp = Cast<ASpawnPoint>(m_spawnPoints[i]);

			if (temp != nullptr && temp->CheckIsActive() == true)
			{
				activeSpawnPoints.Add(m_spawnPoints[i]);
			}
		}

		if (activeSpawnPoints.Num() == 0)
		{
			return;
		}

		int32 rand = FMath::RandRange(0, (activeSpawnPoints.Num() - 1));

		FVector location = activeSpawnPoints[rand]->GetActorLocation();
		location.Y += 90.0f;

		const FRotator rotation = activeSpawnPoints[rand]->GetActorRotation();

		//m_poolRef->SpawnEnemy(location, rotation);

		FActorSpawnParameters spawnParams;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		TSubclassOf<AActor> toSpawn = GenerateToSpawn();

		if (toSpawn == nullptr)
		{
			return;
		}

		AEnemyBase* spawnActor = Cast<AEnemyBase>(GetWorld()->SpawnActor<AActor>(toSpawn, location, rotation, spawnParams));
		spawnActor->Init(spawnActor->m_health, (spawnActor->m_speed + m_enemySpeedBonus), this);

		m_spawnedEnemies.Add(spawnActor);
		m_toSpawn -= 1;

		ASpawnPoint* temp = Cast<ASpawnPoint>(activeSpawnPoints[rand]);
		temp->ResetTimer();

		m_spawnTimer = 0.0f;
	}
}

void AEnemySpawner::SpawnMiniBoss()
{
	if (m_spawnPoints.Num() != 0)
	{
		TArray<AActor*> activeSpawnPoints;

		for (int i = 0; i < m_spawnPoints.Num(); i++)
		{
			ASpawnPoint* temp = Cast<ASpawnPoint>(m_spawnPoints[i]);

			if (temp != nullptr && temp->CheckIsActive() == true)
			{
				activeSpawnPoints.Add(m_spawnPoints[i]);
			}
		}

		if (activeSpawnPoints.Num() == 0)
		{
			return;
		}

		int32 rand = FMath::RandRange(0, (activeSpawnPoints.Num() - 1));

		FVector location = activeSpawnPoints[rand]->GetActorLocation();
		location.Y += 90.0f;

		const FRotator rotation = activeSpawnPoints[rand]->GetActorRotation();

		FActorSpawnParameters spawnParams;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		TSubclassOf<AActor> toSpawn = m_miniBoss;

		if (toSpawn == nullptr)
		{
			return;
		}

		AEnemyBase* spawnActor = Cast<AEnemyBase>(GetWorld()->SpawnActor<AActor>(toSpawn, location, rotation, spawnParams));

		spawnActor->Init(spawnActor->m_health, (spawnActor->m_speed + m_enemySpeedBonus), this);
		m_enemiesAlive += 1;

		ASpawnPoint* temp = Cast<ASpawnPoint>(activeSpawnPoints[rand]);
		temp->ResetTimer();

		m_spawnMiniBoss = false;
		m_waveRef->SetMiniBossCheck(false);
	}
}

void AEnemySpawner::NewWave()
{	
	//m_poolRef->NextWave();
	//m_poolRef->GenerateWave();

	//m_waveLimit = m_poolRef->GetWaveLimit();

	m_waveRef->NextWave();

	m_waveLimit = m_waveRef->GetAmountOfEnemies();
	m_enemySpeedBonus = m_waveRef->GetEnemySpeedBonus();

	m_toSpawn = m_waveLimit;
	m_enemiesAlive = m_waveLimit;
}

void AEnemySpawner::DespawnEnemy(class AEnemyBase* enemy)
{
	if (enemy != nullptr)
	{
		if (m_spawnedEnemies.Contains(enemy))
		{
			m_spawnedEnemies.Remove(enemy);			
		}

		m_enemiesAlive -= 1;
		enemy->Destroy();
	}
}

int AEnemySpawner::GetRemainingEnemies()
{	
	return m_enemiesAlive;
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_waveRef->SpawnMiniBossCheck() == true)
	{
		m_spawnMiniBoss = true;

		if (m_spawnMiniBoss == true)
		{
			SpawnMiniBoss();
		}
	}

	if (m_toSpawn > 0)
	{
		m_spawnTimer += DeltaTime;

		if (m_spawnTimer >= m_spawnDelay)
		{
			SpawnEnemy();
		}
	}
	else
	{
		if (m_spawnedEnemies.Num() == 0)
		{
			NewWave();
		}
	}
}

