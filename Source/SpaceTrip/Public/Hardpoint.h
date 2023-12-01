// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hardpoint.generated.h"

UCLASS()
class SPACETRIP_API AHardpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHardpoint();

	bool CheckForPlayer();

	void SetIsAwake(bool isawake, class AHardpointManager* manager);

	UFUNCTION(BlueprintCallable)
	bool CheckIsAwake();

	void CompleteHardpoint();

	int GetCooldown();
	void SetCooldown(int cooldown);
	void ReduceCooldown();
	void SetIsUnlocked(bool check);
	bool GetIsUnlocked();

	TSubclassOf<AActor> GenerateReward();
	void SpawnBonus(TSubclassOf<AActor> bonus);

	UFUNCTION(BlueprintCallable)
	FString GetName();
	UFUNCTION(BlueprintCallable)
	float GetTimer();
	UFUNCTION(BlueprintCallable)
	bool GetIsActive();
	UFUNCTION(BlueprintCallable)
	void SetIsStarted(bool check);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hardpoint")
		TArray<TSubclassOf<AActor>> m_rewards;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hardpoint")
		TArray<int> rewardRates;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hardpoint")
		FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hardpoint")
		float radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hardpoint")
		int goalTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hardpoint")
		bool isStarted;

private:

	 class AHardpointManager* m_manager;

	AActor* m_player;

	float m_timer;

	int m_cooldown;

	bool m_isUnlocked;
	bool m_isAwake;
	bool m_isActive;
};
