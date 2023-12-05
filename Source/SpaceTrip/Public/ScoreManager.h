// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoreManager.generated.h"

UCLASS()
class SPACETRIP_API AScoreManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScoreManager();

	UFUNCTION(BlueprintCallable)
	void AdjustScore(int value);
	UFUNCTION(BlueprintCallable)
	int GetScore();

private:

	int m_score;
};
