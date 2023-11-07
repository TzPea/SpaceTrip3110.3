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

	void Init(int health, float speed, class AEnemySpawner* spawner);

	UFUNCTION(BlueprintCallable)
	bool GetIsActive();
	void ToggleIsActive();

	UFUNCTION(BlueprintCallable)
	float GetSpeed();
	void SetSpeed(float speed);
	UFUNCTION(BlueprintCallable)
	int GetHealth();
	void SetHealth(int health);

	UFUNCTION(BlueprintCallable)
	virtual void HitActor();
	UFUNCTION(BlueprintCallable)
	virtual void OnDeath();
	UFUNCTION(BlueprintCallable)
	void DestroyEnemy();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float m_health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float m_speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		int m_medHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		int m_lowHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		UStaticMesh* m_fullMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		UStaticMesh* m_medMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		UStaticMesh* m_lowMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		UMaterial* m_fullMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		UMaterial* m_medMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		UMaterial* m_lowMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TSubclassOf<AActor> m_ammoType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int m_ammoChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	class UStaticMeshComponent* m_meshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	class UNiagaraComponent* m_niagara;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	class UNiagaraSystem* m_niagaraSystem;

private:
	UCharacterMovementComponent* m_movementComp;
	class AAIController* m_controller;

	AActor* m_player;

	bool m_isActive;
	class AEnemySpawner* m_spawner;
};
