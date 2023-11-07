
// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"
#include "PlayerBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void APlayerControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_dashTimer < m_dashCooldown)
	{
		m_dashTimer += DeltaTime;
	}
}

void APlayerControllerBase::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);

	m_player = Cast<APlayerBase>(pawn);

	if (m_player != nullptr)
	{
		m_inputComp = Cast<UEnhancedInputComponent>(InputComponent);
	}

	UEnhancedInputLocalPlayerSubsystem* inputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (inputSubsystem != nullptr)
	{
		inputSubsystem->ClearAllMappings();
		inputSubsystem->AddMappingContext(m_inputMappingContext, 0);
	}

	if (m_inputComp != nullptr)
	{
		if (ActionMove)
		{
			m_inputComp->BindAction(ActionMove, ETriggerEvent::Triggered, this, &APlayerControllerBase::Move);
		}

		if (ActionLook)
		{
			m_inputComp->BindAction(ActionLook, ETriggerEvent::Triggered, this, &APlayerControllerBase::Look);
		}

		if (ActionJump)
		{
			m_inputComp->BindAction(ActionJump, ETriggerEvent::Triggered, this, &APlayerControllerBase::Jump);
		}

		if (ActionDash)
		{
			m_inputComp->BindAction(ActionDash, ETriggerEvent::Triggered, this, &APlayerControllerBase::Dash);
		}

		m_dashTimer = m_dashCooldown;
	}
}

void APlayerControllerBase::OnUnPossess()
{
	m_inputComp->ClearActionBindings();

	Super::OnUnPossess();
}

void APlayerControllerBase::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D movementVector = InputActionValue.Get<FVector2D>();

	if (m_player)
	{
		m_player->AddMovementInput(m_player->GetActorForwardVector(), movementVector.Y);
		m_player->AddMovementInput(m_player->GetActorRightVector(), movementVector.X);
	}
}

void APlayerControllerBase::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D lookAxisVector = InputActionValue.Get<FVector2D>();

	AddYawInput(lookAxisVector.X);
	AddPitchInput(lookAxisVector.Y);
}

void APlayerControllerBase::Jump()
{
	if (m_player)
	{
		m_player->Jump();
	}
}

void APlayerControllerBase::Dash()
{
	if (m_player != nullptr && m_dashTimer >= m_dashCooldown)
	{
		FVector velocity = m_player->GetPlayerVelocity();

		FVector momentum = velocity.GetSafeNormal();

		StopMovement();

		m_player->LaunchCharacter(FVector(momentum.X * m_dashPower, momentum.Y * m_dashPower, 0), false, true);

		m_dashTimer = 0;
	}
}
