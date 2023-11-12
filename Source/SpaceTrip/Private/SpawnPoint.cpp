// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPoint.h"
#include "Components/SphereComponent.h"
#include "UObject/Object.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpawnPoint::ASpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASpawnPoint::SetSpawnPoint(float min, float max, float delay)
{
	m_minDistance = min;
	m_maxDistance = max;
	m_spawnDelay = delay;
}

void ASpawnPoint::SetIsActive()
{
	if (m_spawnTimer < m_spawnDelay)
	{
		m_isActive = false;
		return;
	}

	if (m_player != nullptr)
	{
		FVector playerPos = m_player->GetActorLocation();

		FVector spawnPos = GetActorLocation();

		FVector distance = playerPos - spawnPos;

		if (m_minDistance < distance.Size() && distance.Size() < m_maxDistance)
		{
			m_isActive = true;
		}
		else
		{
			m_isActive = false;
		}
	}
}

bool ASpawnPoint::CheckIsActive()
{
	return m_isActive;
}

void ASpawnPoint::ResetTimer()
{
	m_spawnTimer = 0.0f;
}

// Called when the game starts or when spawned
void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	m_player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	m_spawnTimer = 0.0f;
}


// Called every frame
void ASpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_spawnTimer += DeltaTime;
	SetIsActive();
}

