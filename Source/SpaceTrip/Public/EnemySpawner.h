// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()

class SPACETRIP_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	void DespawnEnemy(class AEnemyBase* enemy);
	void KillEnemy(class AEnemyBase* enemy);

	void QueueExtra(TSubclassOf<AActor> extra);
	void QueueExtra(TArray<TSubclassOf<AActor>> extras);

	void GenerateHardpointEnemies(int grapes, int strawberries, int melons, int bosses);
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnEnemy();
	void NewWave();

	void SpawnExtra();

public:	
	UPROPERTY(EditAnywhere)
	class AScoreManager* scoreManager;

	UPROPERTY(EditAnywhere)
	class AWaveHandler* waveRef;

	UPROPERTY(EditAnywhere)
	float despawnDistance;
	UPROPERTY(EditAnywhere)
	float spawnDelay;
	UPROPERTY(EditAnywhere)
	float spawnpointDelay;

	UPROPERTY(EditAnywhere)
	float minDistance;
	UPROPERTY(EditAnywhere)
	float maxDistance;
	UPROPERTY(EditAnywhere)
	float zAxisCheck;

private:

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> m_spawnPoints;

	TArray<TSubclassOf<AActor>> m_toSpawn;
	TArray<TSubclassOf<AActor>> m_toSpawnExtras;

	TArray<AEnemyBase*> m_spawnedEnemies;

	float m_spawnTimer;

	int m_extrasToSpawn;
	int m_amountToSpawn;
	int m_waveLimit;
};
