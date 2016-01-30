// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Religion.h"
#include "Town.generated.h"

UCLASS()
class WOLOLO_API ATown : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATown();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = "Town")
		int32 GetPopulation();

	UFUNCTION(BlueprintPure, Category = "Tiles")
		int32 GetPopulationOfReligion(AReligion* Religion);

	UFUNCTION(BlueprintCallable, Category = "Tiles")
		void AddPopulation(AReligion* Religion, int32 AddedPop);

	TMap<AReligion*, int32> Population;
	
};
