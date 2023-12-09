// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UCLASS()
class SPACETRIP_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBase();

	void Init(int health, float speed, float despawnDist, class AEnemySpawner* spawner);

	UFUNCTION(BlueprintCallable)
	bool GetIsActive();

	UFUNCTION(BlueprintCallable)
	float GetSpeed();
	UFUNCTION(BlueprintCallable)
	int GetHealth();
	void SetHealth(int health);

	UFUNCTION(BlueprintCallable)
	virtual void HitActor();
	UFUNCTION(BlueprintCallable)
	virtual void OnRespawn();
	UFUNCTION(BlueprintCallable)
	virtual void OnDeath();
	UFUNCTION(BlueprintCallable)
	void DestroyEnemy(bool isKilled);

	bool DespawnCheck();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int scoreBonus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int medHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int lowHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	UStaticMesh* fullMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	UStaticMesh* medMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	UStaticMesh* lowMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	UMaterial* fullMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	UMaterial* medMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	UMaterial* lowMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TSubclassOf<AActor> ammoType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int ammoChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	class UNiagaraComponent* niagara;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	class UNiagaraSystem* niagaraSystem;

protected:
	UCharacterMovementComponent* m_movementComp;
	class AAIController* m_controller;

	AActor* m_player;
	FVector m_enemyPos;
	FVector m_playerPos;
	FVector m_distance;

	float m_despawnDistance;

	bool m_isActive;
	class AEnemySpawner* m_spawner;

	float m_despawnTimer;
};
