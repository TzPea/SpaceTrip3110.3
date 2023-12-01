// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySpawner.h"
#include "SpawnPoint.h"
#include "WaveHandler.h"
#include "EnemyBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	spawnDelay = 4.0f;
	m_spawnTimer = 0.0f;
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
				temp->SetSpawnPoint(minDistance, maxDistance, zAxisCheck, spawnpointDelay);
			}
		}
	}
}
#
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

		if (activeSpawnPoints.Num() != 0)
		{
			int32 rand = FMath::RandRange(0, (activeSpawnPoints.Num() - 1));

			FVector location = activeSpawnPoints[rand]->GetActorLocation();
			location.Y += 90.0f;

			const FRotator rotation = activeSpawnPoints[rand]->GetActorRotation();

			FActorSpawnParameters spawnParams;
			spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			TSubclassOf<AActor>* toSpawn = &m_toSpawn[0];

			if (toSpawn != nullptr)
			{
				AEnemyBase* spawnActor = Cast<AEnemyBase>(GetWorld()->SpawnActor<AActor>(*toSpawn, location, rotation, spawnParams));
				spawnActor->Init(spawnActor->GetHealth(), spawnActor->GetSpeed() + waveRef->GetEnemySpeedBonus(), despawnDistance, this);

				m_toSpawn.RemoveAt(0);
				m_amountToSpawn -= 1;
				m_spawnedEnemies.Add(spawnActor);

				ASpawnPoint* temp = Cast<ASpawnPoint>(activeSpawnPoints[rand]);
				temp->ResetTimer();

				m_spawnTimer = 0.0f;
			}
		}
	}
}
void AEnemySpawner::SpawnExtra()
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

		if (activeSpawnPoints.Num() != 0)
		{
			int32 rand = FMath::RandRange(0, (activeSpawnPoints.Num() - 1));

			FVector location = activeSpawnPoints[rand]->GetActorLocation();
			location.Y += 90.0f;

			const FRotator rotation = activeSpawnPoints[rand]->GetActorRotation();

			FActorSpawnParameters spawnParams;
			spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			TSubclassOf<AActor>* toSpawn = &m_toSpawnExtras[0];

			if (toSpawn != nullptr)
			{
				AEnemyBase* spawnActor = Cast<AEnemyBase>(GetWorld()->SpawnActor<AActor>(*toSpawn, location, rotation, spawnParams));
				spawnActor->Init(spawnActor->GetHealth(), spawnActor->GetSpeed() + waveRef->GetEnemySpeedBonus(), despawnDistance, this);

				m_toSpawnExtras.RemoveAt(0);
				m_extrasToSpawn -= 1;

				ASpawnPoint* temp = Cast<ASpawnPoint>(activeSpawnPoints[rand]);
				temp->ResetTimer();

				m_spawnTimer = 0.0f;
			}
		}
	}
}

void AEnemySpawner::NewWave()
{	
	waveRef->NextWave();
	m_toSpawn = waveRef->GenerateWave();
	m_amountToSpawn = m_toSpawn.Num();
}

void AEnemySpawner::QueueExtra(TSubclassOf<AActor> extra)
{
	m_toSpawnExtras.Add(extra);
	m_extrasToSpawn += 1;
}

void AEnemySpawner::QueueExtra(TArray<TSubclassOf<AActor>> extras)
{
	for (int i = 0; i < extras.Num(); i++)
	{
		m_toSpawnExtras.Add(extras[i]);
		m_extrasToSpawn += 1;
	}

	extras.Empty();
}

void AEnemySpawner::GenerateHardpointEnemies(int grapes, int strawberries, int melons, int bosses)
{
	if (grapes > 0)
	{
		for (int i = 0; i < grapes; i++)
		{
			QueueExtra(waveRef->poolEnemies[0]);
		}
	}
	if (strawberries > 0)
	{
		for (int i = 0; i < strawberries; i++)
		{
			QueueExtra(waveRef->poolEnemies[1]);
		}
	}
	if (melons > 0)
	{
		for (int i = 0; i < melons; i++)
		{
			QueueExtra(waveRef->poolEnemies[2]);
		}
	}
	if (bosses > 0)
	{
		for (int i = 0; i < bosses; i++)
		{
			QueueExtra(waveRef->miniBoss);
		}
	}
}

void AEnemySpawner::DespawnEnemy(class AEnemyBase* enemy)
{
	if (enemy != nullptr)
	{
		FString name = enemy->name;

		if (m_spawnedEnemies.Contains(enemy))
		{
			m_spawnedEnemies.Remove(enemy);

			if (name.Compare("Grape") == 0)
			{
				m_toSpawn.Add(waveRef->poolEnemies[0]);
			}
			else if (name.Compare("Strawberry") == 0)
			{
				m_toSpawn.Add(waveRef->poolEnemies[1]);
			}
			else if (name.Compare("Watermelon") == 0)
			{
				m_toSpawn.Add(waveRef->poolEnemies[2]);
			}

			m_amountToSpawn += 1;
		}
		else
		{
			if(name.Compare("Grape") == 0)
			{
				QueueExtra(waveRef->poolEnemies[0]);
			}
			else if (name.Compare("Strawberry") == 0)
			{
				QueueExtra(waveRef->poolEnemies[1]);
			}
			else if (name.Compare("Watermelon") == 0)
			{
				QueueExtra(waveRef->poolEnemies[2]);
			}
			else if (name.Compare("Tank") == 0)
			{
				QueueExtra(waveRef->miniBoss);
			}

		}

		enemy->Destroy();
	}
}

void AEnemySpawner::KillEnemy(AEnemyBase* enemy)
{
	if (enemy != nullptr)
	{
		if (m_spawnedEnemies.Contains(enemy))
		{
			m_spawnedEnemies.Remove(enemy);
		}

		enemy->Destroy();
	}
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_extrasToSpawn > 0)
	{
		SpawnExtra();
	}

	if (m_amountToSpawn > 0)
	{
		m_spawnTimer += DeltaTime;

		if (m_spawnTimer >= spawnDelay)
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

