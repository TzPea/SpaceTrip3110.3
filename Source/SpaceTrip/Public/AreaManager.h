// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AreaManager.generated.h"

UCLASS()
class SPACETRIP_API AAreaManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAreaManager();

	UFUNCTION(BlueprintCallable)
	void SetIsUnlocked(bool check);
	void UpdateSpawnpoints();
	void UpdateHardpoints();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere)
	bool m_isUnlocked;

private:

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<class ASpawnPoint*> m_spawnPoints;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<class AHardpoint*> m_hardPoints;
};
