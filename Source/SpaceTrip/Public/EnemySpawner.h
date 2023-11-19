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

	UFUNCTION(BlueprintCallable)
	int GetRemainingEnemies();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TSubclassOf<AActor> GenerateToSpawn();
	void SpawnEnemy();
	void SpawnMiniBoss();
	void NewWave();

public:	

private:

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AActor>> m_poolEnemies;

	TArray<int> m_spawnRates;

	/*UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class AEnemyPool* m_poolRef;*/

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class AWaveHandler* m_waveRef;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> m_spawnPoints;

	UPROPERTY(VisibleAnywhere, Category = "Spawner")
	TArray<class AEnemyBase*> m_spawnedEnemies;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float m_spawnDelay;
	float m_spawnTimer;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float m_spawnpointDelay;

	UPROPERTY(VisibleAnywhere, Category = "Spawner")
	float m_enemySpeedBonus;
	UPROPERTY(VisibleAnywhere, Category = "Spawner")
	int m_waveLimit;
	UPROPERTY(VisibleAnywhere, Category = "Spawner")
	int m_toSpawn;
	UPROPERTY(EditAnywhere, Category = "Spawner")
	int m_enemiesAlive;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> m_miniBoss;

	bool m_spawnMiniBoss;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float m_minDistance;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float m_maxDistance;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float m_zAxisCheck;
};
