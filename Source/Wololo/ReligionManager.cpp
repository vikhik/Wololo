// Fill out your copyright notice in the Description page of Project Settings.

#include "Wololo.h"
#include "ReligionManager.h"

// Sets default values
AReligionManager::AReligionManager() :
	BasePopulation(250),
	PopulationVariance(100)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ReligionClass = AReligion::StaticClass();
	TownClass = ATown::StaticClass();

	Colors.Add(FColor::FromHex("0000A6"));
	Colors.Add(FColor::FromHex("FFFF00"));
	Colors.Add(FColor::FromHex("1CE6FF"));
	Colors.Add(FColor::FromHex("FF34FF"));
	Colors.Add(FColor::FromHex("FF4A46"));
	Colors.Add(FColor::FromHex("008941"));
	Colors.Add(FColor::FromHex("006FA6"));
	Colors.Add(FColor::FromHex("A30059"));
	Colors.Add(FColor::FromHex("7A4900"));
	Colors.Add(FColor::FromHex("63FFAC"));
	Colors.Add(FColor::FromHex("B79762"));
	Colors.Add(FColor::FromHex("004D43"));
	Colors.Add(FColor::FromHex("8FB0FF"));
	Colors.Add(FColor::FromHex("997D87")); 
	// 16 nice colours, ish, TODO MAKE BETTER
	// http://godsnotwheregodsnot.blogspot.ru/2013/11/kmeans-color-quantization-seeding.html
}

// Called when the game starts or when spawned
void AReligionManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (!TileManager)
	{
		TSubclassOf<ATileManager> ClassToFind = ATileManager::StaticClass();
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, FoundActors);

		if (FoundActors.Num() > 0)
			TileManager = (ATileManager*)FoundActors[0];
	}
}

// Called every frame
void AReligionManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AReligionManager::SpawnReligionAtLocation(FVector Location, ERitualType Type)
{
	UWorld* World = GetWorld();

	AReligion* NewReligion = (AReligion*)World->SpawnActor(ReligionClass, &Location);

	NewReligion->SetNewType(Type);

	AllReligions.Add(NewReligion);
}

void AReligionManager::SpawnNumberReligions(int32 Num)
{
	FTransform ZeroTransform;

	uint8 Type = 0;

	for (uint8 i = 0; i < Num; i++)
	{
		SpawnReligionAtLocation(FVector::ZeroVector, (ERitualType)Type);

		Type++;

		if ((ERitualType)Type == ERitualType::MAX)
		{
			Type = 0;
		}
	}
}

void AReligionManager::SpawnReligionInEveryTown()
{
	UWorld* World = GetWorld();

	TArray<ATile*> TilesWithTowns = TileManager->TilesWithTowns;

	SpawnNumberReligions(TilesWithTowns.Num());

	int i = 0;

	for (AReligion* Religion : AllReligions)
	{
		Religion->SetActorLocation(TilesWithTowns[i]->GetActorLocation());

		int32 RandomPop = BasePopulation + FMath::FRandRange(-PopulationVariance, PopulationVariance);

		((ATile*)TilesWithTowns[i])->AddPopulation(Religion, RandomPop);

		Religion->NumberOfFollowers = RandomPop; // TODO proper updating

		if (i >= Colors.Num())
		{
			Colors.Add(GenerateNewColor());
		}
		
		Religion->Color = Colors[i];

		i++;
		if (i >= TilesWithTowns.Num())
			return; // ERROR LATER, EXIT FOR NOW
	}
}

void AReligionManager::RunUpdate()
{
	// 1. Spread
	for (ATile* Tile : TileManager->Tiles)
	{
		// if A single Religion has 80%+ and over 200 pop
		AReligion* SpreadReligion = Tile->ReadyToSpread();

		if (SpreadReligion)
		{
			auto AdjacentTiles = TileManager->GetAdjacentTiles(Tile);

			auto RandomIndex = FMath::RandRange(0, AdjacentTiles.Num() - 1);

			auto RandomTile = AdjacentTiles[RandomIndex];

			auto SpreadPop = Tile->GetPopulationOfReligion(SpreadReligion) * SpreadReligion->GetSpreadRate();
			auto TargetPop = RandomTile->GetPopulationOfReligion(SpreadReligion); 
			SpreadPop -= TargetPop;

			if (SpreadPop > 0) // Only spread if spreadpop is higher than existing pop
			{
				RandomTile->AddPopulation(SpreadReligion, SpreadPop);
			}
		}
	}

	// 2. Conflict
	for (ATile* Tile : TileManager->Tiles)
	{
		auto Religions = Tile->GetReligions();

		if (Religions.Num() > 1)
		{
			// lowest pop first
			Tile->Population.ValueSort([](int32 PopA, int32 PopB) {
				return PopA < PopB;
			});

			TMap<AReligion*, int32> PopulationChange;

			for (auto ReligiousPopulation : Tile->Population)
			{
				for (auto OtherPopulation : Tile->Population)
				{
					// for each other pop
					// our pop * offense - their pop * defense = their pop change (max 0)

					if (ReligiousPopulation != OtherPopulation)
					{
						int32 PotentialDeaths = ReligiousPopulation.Value * ReligiousPopulation.Key->GetConflictOffense();
						int32 SavedLives = OtherPopulation.Value * OtherPopulation.Key->GetConflictDefense();

						int32 ActualDeaths = PotentialDeaths - SavedLives;

						if (ActualDeaths > 0)
						{
							if (!PopulationChange.Contains(OtherPopulation.Key))
							{
								PopulationChange.Add(OtherPopulation.Key);
							}

							PopulationChange[OtherPopulation.Key] -= ActualDeaths;

							print("Deaths : " + FString::FromInt(ActualDeaths));
						}
					}
				}
			}
		}
	}

	// 3. Growth
	for (ATile* Tile : TileManager->Tiles)
	{
		for (auto ReligiousPopulation : Tile->Population)
		{
			if (ReligiousPopulation.Value < 5000)
			{
				Tile->AddPopulation(ReligiousPopulation.Key, ReligiousPopulation.Value * ReligiousPopulation.Key->GetGrowthRate());
			}
		}
	}
}

FColor AReligionManager::GenerateNewColor()
{
	FVector RandVec = FMath::VRand();
	FColor NewColor = FLinearColor(RandVec).ToFColor(false);

	return NewColor;
}

