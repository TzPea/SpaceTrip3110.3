// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "EnemySpawner.h"
//#include "EnemyAIController.h"
//#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_health = 0;
	//m_attack = 0;
	m_speed = 0;

	m_isActive = false;
}

void AEnemyBase::Init(int health,/* int attack,*/ float speed, AEnemySpawner* spawner)
{
	m_health = health;
	//m_attack = attack;
	m_speed = speed;

	//m_movementComp = Cast<UCharacterMovementComponent>(GetMovementComponent());

	//if (m_movementComp != nullptr)
	//{
	//	m_movementComp->MaxWalkSpeed = m_speed;
	//}

	//m_controller = Cast<AEnemyAIController>(GetController());
	m_spawner = spawner;
	m_isActive = true;
}

bool AEnemyBase::GetIsActive()
{
	return m_isActive;
}

void AEnemyBase::ToggleIsActive()
{
	m_isActive = !m_isActive;
}

float AEnemyBase::GetSpeed()
{
	return m_speed;
}

void AEnemyBase::SetSpeed(float speed)
{
	m_speed = speed;
}

int AEnemyBase::GetHealth()
{
	return m_health;
}

void AEnemyBase::SetHealth(int health)
{
	m_health = health;
}

void AEnemyBase::OnDeath()
{
	if (m_spawner != nullptr)
	{
		m_spawner->DespawnEnemy(this);
	}

	Destroy();
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (m_isActive == true)
	//{
	//	if (m_controller != nullptr)
	//	{
	//		m_controller->MoveToPlayer();
	//	}
	//}
}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}