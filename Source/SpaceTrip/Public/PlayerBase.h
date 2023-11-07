// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerBase.generated.h"

UCLASS()
class SPACETRIP_API APlayerBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerBase();

	FVector GetPlayerVelocity();

	void CheckMovement();

	UFUNCTION(BlueprintCallable)
	bool GetIsMoving();
	UFUNCTION(BlueprintCallable)
	bool GetIsFalling();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	USoundWave* m_walkingSound;

	UPROPERTY(EditAnywhere)
	int m_maxHealth;

	int m_health;

	UPROPERTY(EditAnywhere)
	int m_grapeAmmo;
	UPROPERTY(EditAnywhere)
	int m_strawberryAmmo;
	UPROPERTY(EditAnywhere)
	int m_melonAmmo;

private:

	float m_timeAlive;

	bool m_hasWeapon;
	bool m_isMoving;
	bool m_isFalling;
};
