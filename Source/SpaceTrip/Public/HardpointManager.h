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

	void EndCheckpoints();
	void SetActiveHardpoint();
	void ResetHardpoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> m_hardPoints;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> m_key;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int m_hardpointCooldown;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int m_finalCheckpoint;
	int m_checkpoint;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int m_baseKeyChance;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int m_keyChanceIncrement;

	int m_keyChance;

	class AHardpoint* m_activeHardpoint;
	bool m_hasActive;
	bool m_checkpointsComplete;
};
