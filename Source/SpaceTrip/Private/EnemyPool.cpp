// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyPool.h"
#include "WaveHandler.h"
#include "EnemyBase.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AEnemyPool::AEnemyPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

int AEnemyPool::GenerateWave()
{
	int toSpawn = m_handlerRef->GetAmountOfEnemies();

	m_enemyPool.SetNum(toSpawn);

	for (int u = 0; u < toSpawn; u++)
	{
		AEnemyBase* temp = PoolEnemy();

		if (temp != nullptr)
		{
			m_enemyPool[u] = temp;
		}
	}

	return toSpawn;
}

void AEnemyPool::NextWave()
{
	m_handlerRef->NextWave();
}

AEnemyBase* AEnemyPool::PoolEnemy()
{
	FVector location(0.0f, 0.0f, 90.f);
	FRotator rotation = FRotator().ZeroRotator;

	if (m_poolEnemy)
	{
		UWorld* world = GetWorld();

		if (world)
		{
			FActorSpawnParameters spawnParams;
			spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			AEnemyBase* spawnActor = Cast<AEnemyBase>(world->SpawnActor<AActor>(m_poolEnemy, location, rotation, spawnParams));

			if (spawnActor)
			{
				spawnActor->GetRootComponent()->SetVisibility(false);
				return spawnActor;
			} 

		}
	}

	return nullptr;
}

void AEnemyPool::SpawnEnemy(FVector location, FRotator rotation)
{
	AEnemyBase* enemy = m_enemyPool.Pop();

	//enemy->GetRootComponent()->SetVisibility(true);

	enemy->SetActorLocation(location);
	enemy->SetActorRotation(rotation);

	m_enemyPool.Remove(enemy);
	m_activeEnemies.Add(enemy);
}
void AEnemyPool::SpawnEnemy(AEnemyBase* enemy, FVector location, FRotator rotation)
{
	//enemy->GetRootComponent()->SetVisibility(true);

	enemy->SetActorLocation(location);
	enemy->SetActorRotation(rotation);

	m_enemyPool.Remove(enemy);
	m_activeEnemies.Add(enemy);
}

void AEnemyPool::ReturnToPool(AEnemyBase* enemy)
{
	//enemy->GetRootComponent()->SetVisibility(false);

	m_enemyPool.Add(enemy);

	if (m_activeEnemies.Contains(enemy))
	{
		m_activeEnemies.Remove(enemy);
	}
}

TArray<AEnemyBase*> AEnemyPool::GetActiveEnemies()
{
	return m_activeEnemies;
}

int AEnemyPool::GetWaveLimit()
{
	return m_handlerRef->GetAmountOfEnemies();
}

// Called when the game starts or when spawned
void AEnemyPool::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

