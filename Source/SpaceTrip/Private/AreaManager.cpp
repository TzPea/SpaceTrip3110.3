// Fill out your copyright notice in the Description page of Project Settings.


#include "AreaManager.h"
#include "SpawnPoint.h"

// Sets default values
AAreaManager::AAreaManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_isUnlocked = false;
}

void AAreaManager::SetIsUnlocked(bool check)
{
	if (m_isUnlocked != check)
	{
		m_isUnlocked = check;
		UpdateSpawnpoints();
	}
}

void AAreaManager::UpdateSpawnpoints()
{
	if (m_spawnPoints.Num() != 0)
	{
		for (int i = 0; i < m_spawnPoints.Num(); i++)
		{
			m_spawnPoints[i]->SetIsUnlocked(m_isUnlocked);
		}
	}
}

// Called when the game starts or when spawned
void AAreaManager::BeginPlay()
{
	Super::BeginPlay();
	
	UpdateSpawnpoints();
}

// Called every frame
void AAreaManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

