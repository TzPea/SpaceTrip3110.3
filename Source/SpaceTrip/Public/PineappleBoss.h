// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "PineappleBoss.generated.h"

/**
 * 
 */
UCLASS()
class SPACETRIP_API APineappleBoss : public AEnemyBase
{
	GENERATED_BODY()
	
public:
	APineappleBoss();

	void HitActor() override;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	UStaticMeshComponent* tankMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	UStaticMesh* tankFullMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	UStaticMesh* tankMedMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	UStaticMesh* tankLowMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	UMaterial* tankFullMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	UMaterial* tankMedMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	UMaterial* tankLowMaterial;
};
