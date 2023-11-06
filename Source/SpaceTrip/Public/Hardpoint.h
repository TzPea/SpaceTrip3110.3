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

	void SetIsAwake(bool isawake);

	UFUNCTION(BlueprintCallable)
	bool CheckIsAwake();

	void CompleteHardpoint();

	int GetCooldown();
	void SetCooldown(int cooldown);
	void ReduceCooldown();

	TSubclassOf<AActor> GenerateReward();
	void SpawnBonus(TSubclassOf<AActor> bonus);

	UFUNCTION(BlueprintCallable)
	FString GetName();
	UFUNCTION(BlueprintCallable)
	float GetTimer();
	UFUNCTION(BlueprintCallable)
	bool GetIsActive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:


private:

	AActor* m_player;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Hardpoint")
	TArray<TSubclassOf<AActor>> m_rewards;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Hardpoint")
	TArray<int> m_rewardRates;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Hardpoint")
	FString m_name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Hardpoint")
	float m_radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Hardpoint")
	int m_goalTime;
	float m_timer;

	int m_cooldown;

	bool m_isAwake;
	bool m_isActive;
};
