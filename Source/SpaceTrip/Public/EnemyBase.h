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

	void Init(int health, /*int attack,*/ float speed, class AEnemySpawner* spawner);

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
	virtual void OnDeath();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float m_speed;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int m_health;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//int m_attack;
	//UCharacterMovementComponent* m_movementComp;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//class AEnemyAIController* m_controller;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool m_isActive;
	class AEnemySpawner* m_spawner;
};
