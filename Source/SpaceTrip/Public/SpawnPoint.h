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
	void SetSpawnPoint(float min, float max, float delay);
	void SetIsActive();
	bool CheckIsActive();
	void ResetTimer();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	AActor* m_player;

protected:
	bool m_isActive;

	float m_minDistance;
	float m_maxDistance;

private:
	float m_spawnTimer;
	float m_spawnDelay;

};
