// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPoint.generated.h"

UCLASS()
class SPACETRIP_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPoint();
	void SetSpawnPoint(float min, float max, float zcheck, float delay);
	void SetIsActive();
	bool CheckIsActive();
	void ResetTimer();

	void SetIsUnlocked(bool check);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	AActor* m_player;

protected:
	bool m_isUnlocked;
	bool m_isActive;

	float m_minDistance;
	float m_maxDistance;

	float m_zAxisClamp;

private:
	float m_spawnTimer;
	float m_spawnDelay;

};
