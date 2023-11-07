// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)

class SPACETRIP_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:


	virtual void OnPossess(APawn* pawn) override;
	virtual void OnUnPossess() override;

	void Move(const struct FInputActionValue& InputActionValue);
	void Look(const struct FInputActionValue& InputActionValue);
	void Jump();
	void Dash();

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input")
	class UInputAction* ActionMove;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input")
	class UInputAction* ActionJump;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input")
	class UInputAction* ActionLook;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input")
	class UInputAction* ActionInteract;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input")
	class UInputAction* ActionDash;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Input")
	TObjectPtr<class UInputMappingContext> m_inputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Player Input")
	float m_dashCooldown;
	UPROPERTY(EditAnywhere, Category = "Player Input")
	float m_dashPower;

private:

	UPROPERTY()
	class UEnhancedInputComponent* m_inputComp;

	UPROPERTY()
	class APlayerBase* m_player;
	
	float m_dashTimer;
};
