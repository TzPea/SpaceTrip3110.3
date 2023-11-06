// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyPool.generated.h"

UCLASS()

class SPACETRIP_API AEnemyPool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyPool();

	int GenerateWave();
	void NextWave();
	class AEnemyBase* PoolEnemy();
	void SpawnEnemy(FVector location, FRotator rotation);
	void SpawnEnemy(class AEnemyBase* enemy, FVector location, FRotator rotation);
	void ReturnToPool(class AEnemyBase* enemy);
	TArray<class AEnemyBase*> GetActiveEnemies();
	int GetWaveLimit();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class AWaveHandler* m_handlerRef;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> m_poolEnemy;

	UPROPERTY(VisibleAnywhere, Category = "Pool")
	TArray<class AEnemyBase*> m_enemyPool;
	UPROPERTY(VisibleAnywhere, Category = "Pool")
	TArray<class AEnemyBase*> m_activeEnemies;
};
