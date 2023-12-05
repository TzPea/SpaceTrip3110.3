// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HardpointManager.generated.h"

UCLASS()
class SPACETRIP_API AHardpointManager : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AHardpointManager();

	AActor* GetRandomHardpoint();
	AActor* GetNextHardpoint();

	void GenerateRandomEvent();

	void EndCheckpoints();
	void SetActiveHardpoint();
	void ResetHardpoint();

	UFUNCTION(BlueprintCallable)
	int GetHardpointsComplete();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	class AScoreManager* scoreManager;
	UPROPERTY(EditAnywhere)
	int hardpointCompletionScore;

	UPROPERTY(EditAnywhere)
	class AEnemySpawner* enemySpawner;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> hardPoints;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> key;

	UPROPERTY(EditAnywhere)
	int hardpointCooldown;
	UPROPERTY(EditAnywhere)
	float delayBetweenHardpoints;

	UPROPERTY(EditAnywhere)
	int finalCheckpoint;

	UPROPERTY(EditAnywhere)
	int baseKeyChance;
	UPROPERTY(EditAnywhere)
	int keyChanceIncrement;

	UPROPERTY(EditAnywhere)
	TArray<int> eventOne;
	UPROPERTY(EditAnywhere)
	TArray<int> eventTwo;
	UPROPERTY(EditAnywhere)
	TArray<int> eventThree;
	UPROPERTY(EditAnywhere)
	TArray<int> eventFour;
private:
	int m_checkpoint;
	int m_hardpointsComplete;

	float m_delayTimer;

	int m_keyChance;

	class AHardpoint* m_activeHardpoint;
	bool m_hasActive;
	bool m_checkpointsComplete;
};
