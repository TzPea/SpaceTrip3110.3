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
	UFUNCTION(BlueprintCallable)
	float GetEnemySpeedBonus();
	int GetAmountOfEnemies();
	void IncrementSpawnRates();
	TArray<int> GetSpawnRates();

	void SetMiniBossCheck(bool check);
	bool SpawnMiniBossCheck();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	//UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	//class AEnemyPool* m_poolRef;


	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int m_amountOfEnemiesIncrement;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int m_amountOfEnemies;

	int m_wave;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float m_enemySpeedBonusIncrement;
	float m_enemySpeedBonus;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int m_difIncreaseCooldown;
	int m_difIncreaseTimer;

	TArray<int> m_spawnRates;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<int> m_baseSpawnRates;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int m_checkpointWaveOne;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<int> m_spawnRatesOne;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int m_checkpointWaveTwo;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<int> m_spawnRatesTwo;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<float> m_spawnRateIncrement;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int m_incrementDelay;

	int m_incrementCooldown;
	bool m_startIncrement;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int m_miniBossDelay;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<class USoundWave*> m_waveSounds;


	int m_miniBossCooldown;
	bool m_spawnMiniBoss;
};
