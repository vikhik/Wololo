// Fill out your copyright notice in the Description page of Project Settings.

#include "Wololo.h"
#include "Tile.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

AReligion* ATile::ReadyToSpread()
{
	for (auto Religion : GetReligions())
	{
		if (GetReligiousPercentage(Religion) > Religion->GetSpreadMinimumPercentage()
			&& GetPopulationOfReligion(Religion) > Religion->GetSpreadMinimumPopulation())
		{
			return Religion;
		}
	}

	return nullptr;
}

TArray<AReligion*> ATile::GetReligions()
{
	TArray<AReligion*> Religions;

	for (auto ReligiousPopulation : Population)
	{
		Religions.Add(ReligiousPopulation.Key);
	}

	if (Town)
	{
		for (auto ReligiousPopulation : Town->Population)
		{
			if (!Religions.Contains(ReligiousPopulation.Key))
				Religions.Add(ReligiousPopulation.Key);
		}
	}

	return Religions;
}

float ATile::GetReligiousPercentage(AReligion* Religion)
{
	if (GetPopulation() == 0)
		return 0;

	return (float)GetPopulationOfReligion(Religion) / (float)GetPopulation();
}

void ATile::SetWidthAndHeight(float NewWidth, float NewHeight)
{
	this->Width = NewWidth;
	this->Height = NewHeight;
}

int32 ATile::GetPopulation()
{
	int32 BasePopulation = 0;
	for (auto ReligiousPopulation : Population)
		BasePopulation += ReligiousPopulation.Value;

	if (Town)
		return BasePopulation + Town->GetPopulation();
	else
		return BasePopulation;
}

int32 ATile::GetPopulationOfReligion(AReligion* Religion)
{
	int32 Pop = 0;

	if (Town)
	{
		Pop += Town->GetPopulationOfReligion(Religion);
	}
	else
	{
		if (Population.Contains(Religion))
			Pop += Population[Religion];
	}

	return Pop;
}

void ATile::AddPopulation(AReligion* Religion, int32 AddedPop)
{
	if (Town)
	{
		Town->AddPopulation(Religion, AddedPop);
	}
	else
	{
		if (!Population.Contains(Religion))
			Population.Add(Religion, 0);

		Population[Religion] += AddedPop;

		if (Population[Religion] <= 0)
		{
			Population.Remove(Religion);
		}
	}
}

