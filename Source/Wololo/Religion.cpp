// Fill out your copyright notice in the Description page of Project Settings.

#include "Wololo.h"
#include "Religion.h"


// Sets default values
AReligion::AReligion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NumberOfFollowers = 1000;
}

// Called when the game starts or when spawned
void AReligion::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AReligion::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

float AReligion::GetSpreadMinimumPercentage()
{
	float SpreadMinimumPercentage = 0.f;

	for (auto Influence : RitualInfluences)
	{
		FRitualData RitualData = RitualManager::GetInstance()->RitualMap[Influence.Key];

		SpreadMinimumPercentage += RitualData.SpreadMinimumPercentage * Influence.Value;
	}

	return SpreadMinimumPercentage;
}

int32 AReligion::GetSpreadMinimumPopulation()
{
	int32 SpreadMinimumPopulation = 0;

	for (auto Influence : RitualInfluences)
	{
		FRitualData RitualData = RitualManager::GetInstance()->RitualMap[Influence.Key];

		SpreadMinimumPopulation += RitualData.SpreadMinimumPopulation * Influence.Value;
	}

	return SpreadMinimumPopulation;
}

float AReligion::GetSpreadRate()
{
	float SpreadRate = 0.f;

	for (auto Influence : RitualInfluences)
	{
		FRitualData RitualData = RitualManager::GetInstance()->RitualMap[Influence.Key];

		SpreadRate += RitualData.SpreadRate * Influence.Value;
	}

	return SpreadRate;
}

float AReligion::GetConflictOffense()
{
	float ConflictOffense = 0.f;

	for (auto Influence : RitualInfluences)
	{
		FRitualData RitualData = RitualManager::GetInstance()->RitualMap[Influence.Key];

		ConflictOffense += RitualData.ConflictOffense * Influence.Value;
	}

	return ConflictOffense;
}

float AReligion::GetConflictDefense()
{
	float ConflictDefense = 0.f;

	for (auto Influence : RitualInfluences)
	{
		FRitualData RitualData = RitualManager::GetInstance()->RitualMap[Influence.Key];

		ConflictDefense += RitualData.ConflictDefense * Influence.Value;
	}

	return ConflictDefense;
}

float AReligion::GetGrowthRate()
{
	float GrowthRate = 0.f;

	for (auto Influence : RitualInfluences)
	{
		FRitualData RitualData = RitualManager::GetInstance()->RitualMap[Influence.Key];

		GrowthRate += RitualData.GrowthRate * Influence.Value;
	}

	return GrowthRate;
}

void AReligion::SetNewType(ERitualType Type)
{
	for (auto Influence : RitualInfluences)
	{
		Influence.Value = 0.f;
	}

	CurrentType = Type;

	if (!RitualInfluences.Contains(Type))
		RitualInfluences.Add(Type);

	RitualInfluences[Type] = 1.0f;
}

