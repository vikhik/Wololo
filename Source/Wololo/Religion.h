// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RitualData.h"
#include "RitualManager.h"
#include "Religion.generated.h"

UCLASS()
class WOLOLO_API AReligion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AReligion();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// TRAIT VALUES

	UFUNCTION(BlueprintCallable, Category = "Religion")
		float GetSpreadMinimumPercentage();

	UFUNCTION(BlueprintCallable, Category = "Religion")
		int32 GetSpreadMinimumPopulation();

	UFUNCTION(BlueprintCallable, Category = "Religion")
		float GetSpreadRate();

	UFUNCTION(BlueprintCallable, Category = "Religion")
		float GetConflictOffense();

	UFUNCTION(BlueprintCallable, Category = "Religion")
		float GetConflictDefense();

	UFUNCTION(BlueprintCallable, Category = "Religion")
		float GetGrowthRate();


	// Other stuff

	TMap<ERitualType, float> RitualInfluences; // 0.0 - 1.0
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FColor Color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 NumberOfFollowers;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ERitualType CurrentType;

	UFUNCTION(BlueprintCallable, Category = "Religion")
		void SetNewType(ERitualType Type);
};
