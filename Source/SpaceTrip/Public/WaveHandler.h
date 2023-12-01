// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveHandler.generated.h"

UCLASS()
class SPACETRIP_API AWaveHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveHandler();
	void NextWave();

	UFUNCTION(BlueprintCallable)
	int GetWave();
	float GetEnemySpeedBonus();

	TArray<TSubclassOf<AActor>> GenerateWave();
	TSubclassOf<AActor> GenerateEnemy();

	void IncrementSpawnRates();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:

	UPROPERTY(EditAnywhere)
	class AEnemySpawner* spawnerRef;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> poolEnemies;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> miniBoss;

	UPROPERTY(EditAnywhere)
	int amountOfEnemiesIncrement;
	UPROPERTY(EditAnywhere)
	int amountOfEnemiesBase;

	UPROPERTY(EditAnywhere)
	float enemySpeedBonusIncrement;

	UPROPERTY(EditAnywhere)
	int statIncreaseCooldown;

	UPROPERTY(EditAnywhere)
	int waveToIntroduceStrawberries;

	UPROPERTY(EditAnywhere)
	int waveToIntroduceMelons;

	UPROPERTY(EditAnywhere)
	TArray<float> spawnRatesIncrement;
	UPROPERTY(EditAnywhere)
	int spawnRatesIncrementDelay;

	UPROPERTY(EditAnywhere)
	int miniBossDelay;

	UPROPERTY(EditAnywhere)
	TArray<class USoundWave*> waveSounds;
private:

	UPROPERTY(VisibleAnywhere)
	int m_wave;

	float m_enemySpeedBonus;

	int m_difIncreaseTimer;

	TArray<int> m_spawnRates;

	int m_incrementCooldown;
	bool m_startIncrement;

	int m_miniBossCooldown;
	bool m_spawnMiniBoss;
};
