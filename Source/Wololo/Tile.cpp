// Fill out your copyright notice in the Description page of Project Settings.

#include "Wololo.h"
#include "Tile.h"

float ATile::ConversionRate = 1 / 2;

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

bool ATile::HasConflictingReligion(AReligion* Religion)
{
	auto Religions = GetReligions();

	for (auto OtherReligion : Religions)
	{
		if (OtherReligion != Religion)
			return true;
	}

	return false;
}

bool ATile::HasPotentialTargetNeighbour(AReligion* Religion)
{
	for (auto Tile : Neighbours)
	{
		if (Tile->HasConflictingReligion(Religion))
		{
			return true;
		}

		if (Tile->GetPopulationOfReligion(Religion) == 0)
		{
			return true;
		}
	}

	return false;
}

bool ATile::IsEmpty()
{
	return GetPopulation() == 0;
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

TMap<AReligion*, int32> ATile::GetPopulationByReligion()
{
	// TODO: If we ever spawn Towns later...
	if (Town)
	{
		return Town->Population;
	}
	else
	{
		return Population;
	}
}

void ATile::Attack(AReligion* Religion, AReligion* TargetReligion)
{
	int32 AttackerStrength = GetPopulationOfReligion(Religion);
	int32 DefenderStrength = GetPopulationOfReligion(TargetReligion);

	if (Religion->GetHighestRitualType() == ERitualType::Aggressive)
	{
		AttackerStrength *= 2;
	}

	if (TargetReligion->GetHighestRitualType() == ERitualType::Meditiative)
	{
		DefenderStrength *= 2;
	}

	int32 Deaths = FMath::Min(AttackerStrength, DefenderStrength);

	AddPopulation(Religion, -Deaths);
	AddPopulation(TargetReligion, -Deaths);
}

void ATile::Convert(AReligion* Religion)
{
	for (auto OtherReligion : GetReligions())
	{
		int32 Audience = GetPopulationOfReligion(OtherReligion);
		int32 Converted = Audience * ATile::ConversionRate;

		AddPopulation(OtherReligion, -Converted);

		int32 CurrentPop = GetPopulationOfReligion(Religion);
		int32 MaxPop = Religion->GetGrowthCap();

		if (CurrentPop + Converted >= MaxPop)
		{
			Converted = MaxPop - CurrentPop;
		}
		if (Converted > 0)
		{
			AddPopulation(Religion, Converted);
		}
	}
}

void ATile::MovePopulation(ATile* EnemyTile, AReligion* Religion, float Ratio, int32 KeepAtLeast)
{
	int32 TotalPop = GetPopulationOfReligion(Religion);

	int32 Segment = TotalPop * Ratio;

	if (TotalPop - Segment < KeepAtLeast)
		return;

	AddPopulation(Religion, -Segment);
	EnemyTile->AddPopulation(Religion, Segment);
}

void ATile::Grow(AReligion* Religion)
{
	int32 CurrentPop = GetPopulationOfReligion(Religion);
	int32 MaxPop = Religion->GetGrowthCap();

	float GrowthRate = Religion->GetGrowthRate();

	if (CurrentPop > MaxPop)
	{
		return;
	}
	else if (CurrentPop > MaxPop * 0.75)
	{
		GrowthRate /= 4;
	}
	else if (CurrentPop > MaxPop * 0.5)
	{
		GrowthRate /= 2;
	}

	int32 GrowthAmount = CurrentPop * GrowthRate;

	if (CurrentPop >= Religion->GetGrowthCap())
	{
		return;
	}
	else if (CurrentPop + GrowthAmount >= MaxPop)
	{
		GrowthAmount = MaxPop - CurrentPop;
	}

	AddPopulation(Religion, GrowthAmount);
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

