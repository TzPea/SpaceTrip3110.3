// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreManager.h"

// Sets default values
AScoreManager::AScoreManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_score = 0;
}

void AScoreManager::AdjustScore(int value)
{
	m_score += value;
}

int AScoreManager::GetScore()
{
	return m_score;
}

