// Fill out your copyright notice in the Description page of Project Settings.


#include "PineappleBoss.h"

APineappleBoss::APineappleBoss()
{
	tankMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TankMeshComponent"));
	tankMeshComp->SetupAttachment(RootComponent);
}

void APineappleBoss::HitActor()
{
	health -= 1;

	if (meshComp != nullptr && tankMeshComp != nullptr)
	{
		int numberOfMaterials;

		if (health == medHP)
		{
			meshComp->SetStaticMesh(medMesh);
			tankMeshComp->SetStaticMesh(tankMedMesh);

			numberOfMaterials = meshComp->GetNumMaterials();

			for (int i = 0; i < numberOfMaterials; i++)
			{
				if (meshComp->GetMaterial(i))
				{
					meshComp->SetMaterial(i, medMaterial);
				}
			}

			numberOfMaterials = tankMeshComp->GetNumMaterials();

			for (int i = 0; i < numberOfMaterials; i++)
			{
				if (tankMeshComp->GetMaterial(i))
				{
					tankMeshComp->SetMaterial(i, tankMedMaterial);
				}
			}
		}
		else if (health == lowHP)
		{
			meshComp->SetStaticMesh(lowMesh);
			tankMeshComp->SetStaticMesh(tankLowMesh);

			numberOfMaterials = meshComp->GetNumMaterials();

			for (int i = 0; i < numberOfMaterials; i++)
			{
				if (meshComp->GetMaterial(i))
				{
					meshComp->SetMaterial(i, lowMaterial);
				}
			}

			numberOfMaterials = tankMeshComp->GetNumMaterials();

			for (int i = 0; i < numberOfMaterials; i++)
			{
				if (tankMeshComp->GetMaterial(i))
				{
					tankMeshComp->SetMaterial(i, tankLowMaterial);
				}
			}
		}
		else if (health <= 0)
		{
			meshComp->SetStaticMesh(nullptr);
			tankMeshComp->SetStaticMesh(nullptr);

			OnDeath();
		}
	}
}
