// Fill out your copyright notice in the Description page of Project Settings.

#include "Wololo.h"
#include "Town.h"


// Sets default values
ATown::ATown()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATown::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATown::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

int32 ATown::GetPopulation()
{
	int32 BasePopulation = 0;
	for (auto ReligiousPopulation : Population)
		BasePopulation += ReligiousPopulation.Value;

	return BasePopulation;
}

int32 ATown::GetPopulationOfReligion(AReligion* Religion)
{
	int32 Pop = 0;

	if (Population.Contains(Religion))
		Pop += Population[Religion];

	return Pop;
}

