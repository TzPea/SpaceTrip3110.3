// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "EnemySpawner.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_health = 0;
	m_speed = 0;

	m_isActive = false;
}

void AEnemyBase::Init(int health,/* int attack,*/ float speed, AEnemySpawner* spawner)
{
	m_health = health;
	m_speed = speed;

	m_movementComp = Cast<UCharacterMovementComponent>(GetMovementComponent());

	if (m_movementComp != nullptr)
	{
		m_movementComp->MaxWalkSpeed = m_speed;
	}

	m_controller = Cast<AAIController>(GetController());
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
void AEnemyBase::HitActor()
{
	m_health -= 1;

	if (m_meshComp != nullptr)
	{
		int numberOfMaterials;

		if (m_health == m_medHP)
		{
			m_meshComp->SetStaticMesh(m_medMesh);

			numberOfMaterials = m_meshComp->GetNumMaterials();

			for (int i = 0; i < numberOfMaterials; i++)
			{
				if (m_meshComp->GetMaterial(i))
				{
					m_meshComp->SetMaterial(i, m_medMaterial);
				}
			}
		}
		else if (m_health == m_lowHP)
		{
			m_meshComp->SetStaticMesh(m_lowMesh);

			numberOfMaterials = m_meshComp->GetNumMaterials();

			for (int i = 0; i < numberOfMaterials; i++)
			{
				if (m_meshComp->GetMaterial(i))
				{
					m_meshComp->SetMaterial(i, m_lowMaterial);
				}
			}
		}
		else if (m_health <= 0)
		{
			m_meshComp->SetStaticMesh(nullptr);

			OnDeath();
		}
	}
}
void AEnemyBase::OnDeath()
{
	if (m_spawner != nullptr)
	{
		m_spawner->DespawnEnemy(this);
	}

	if (m_niagaraSystem != nullptr)
	{
		m_niagara = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), m_niagaraSystem, GetActorLocation());
		m_niagara->Activate();
	}

	FTimerHandle deathHandle;
	GetWorldTimerManager().SetTimer(deathHandle, this, &AEnemyBase::DestroyEnemy, 2.0f, false);

	DestroyEnemy();
}

void AEnemyBase::DestroyEnemy()
{
	int rand = FMath::RandRange(1, 100);

	if (rand <= m_ammoChance)
	{
		FVector location = GetActorLocation();
		location.Z = 90.0f;
		FRotator rotation = GetActorRotation();

		GetWorld()->SpawnActor<AActor>(m_ammoType, location, rotation);
	}

	Destroy();
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	m_player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	TArray<UStaticMeshComponent*> mesh;
	GetComponents<UStaticMeshComponent>(mesh);

	for (int32 i = 0; i < mesh.Num(); i++)
	{
		m_meshComp = mesh[i];
	}
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_isActive == true)
	{
		if (m_controller != nullptr && m_player != nullptr)
		{
			m_controller->MoveTo(m_player);
		}
		else if (m_player == nullptr)
		{
			m_player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		}
	}
}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}