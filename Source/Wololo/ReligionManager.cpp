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

		ATile* Tile = ((ATile*)TilesWithTowns[i]);
		Tile->AddPopulation(Religion, RandomPop);

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
	bool DoDebug = true;
	for (AReligion* Religion : AllReligions)
	{
		ATile* TargetTile;
		ERitualType RitualType = Religion->GetHighestRitualType();

		if (RitualType == ERitualType::Aggressive)
		{
			TargetTile = CalculateNearestEnemyTile(Religion);
		}
		else
		{
			TargetTile = CalculateNearestEmptyTile(Religion);
		}

		for (ATile* Tile : TileManager->Tiles)
		{
			int32 OurPopulation = Tile->GetPopulationOfReligion(Religion);

			if (OurPopulation > 0)
			{
				bool TileConflicted = Tile->HasConflictingReligion(Religion);

				if (TileConflicted)
				{
					ConsiderAndDoAttack(Tile, Religion, RitualType);
					if (DoDebug) print("Attacking Self");
				}
				else
				{
					auto AdjacentTiles = TileManager->GetAdjacentTiles(Tile);

					ATile* EnemyTile = nullptr;

					for (auto AdjacentTile : AdjacentTiles)
					{
						if (AdjacentTile->HasConflictingReligion(Religion))
						{
							EnemyTile = AdjacentTile;
							break;
						}
					}

					if (EnemyTile != nullptr)
					{
						// Adjacent Enemy tile

						if (RitualType != ERitualType::Meditiative)
						{
							Tile->MovePopulation(EnemyTile, Religion, Religion->GetAttackRate());
						}
						else
						{
							// Do Conversion
						}

						ConsiderAndDoAttack(EnemyTile, Religion, RitualType);
						if (DoDebug) print("Attacking Adjacent");
					}
					else
					{
						// No Adjacent Enemy tile
						ATile* NearbyTileInDirection = TileManager->GetTileInDirection(Tile, TargetTile);

						if (NearbyTileInDirection)
						{
							// Move towards target
							Tile->MovePopulation(NearbyTileInDirection, Religion, Religion->GetMoveRate());
							if (DoDebug) print("Moving");
						}
						else
						{
							if (DoDebug) print("Can't Move?");
						}
					}
				}
				
				// Now Grow:
				Tile->Grow(Religion);
				if (DoDebug) print("Growing");
			}
		}

		DoDebug = false;
	}

	// 4. Housekeeping
	for (AReligion* Religion : AllReligions)
	{
		Religion->Followers = 0;

		for (ATile* Tile : TileManager->Tiles)
		{
			Religion->Followers += Tile->GetPopulationOfReligion(Religion);
		}
	}
}

void AReligionManager::ConsiderAndDoAttack(ATile* Tile, AReligion* Religion, ERitualType RitualType)
{
	// Figure out target
	AReligion* TargetReligion = nullptr;

	for (auto OtherReligion : Tile->GetReligions())
	{
		if (Religion != OtherReligion)
		{
			TargetReligion = OtherReligion;
			break;
		}
	}

	if (TargetReligion == nullptr) 
		return; // ERROR? SHOULD NEVER HAPPEN

	int32 OurPopulation = Tile->GetPopulationOfReligion(Religion);
	int32 TheirPopulation = Tile->GetPopulationOfReligion(TargetReligion);

	// Consider Battle
	bool WantToBattle = false;

	switch (RitualType)
	{
	case ERitualType::Aggressive:
		if (OurPopulation >= TheirPopulation * 1.5)
			WantToBattle = true;
		break;

	case ERitualType::Communal:
		if (OurPopulation >= TheirPopulation * 3)
			WantToBattle = true;
		break;

	case ERitualType::Meditiative:
		Tile->Convert(Religion);
		return;
	}

	// Do Battle
	if (WantToBattle)
		Tile->Attack(Religion, TargetReligion);
}

FColor AReligionManager::GenerateNewColor()
{
	FVector RandVec = FMath::VRand();
	FColor NewColor = FLinearColor(RandVec).ToFColor(false);

	return NewColor;
}

ATile* AReligionManager::CalculateNearestEnemyTile(AReligion* Religion)
{
	TArray<ATile*> Tiles;
	TArray<ATile*> CheckedTiles;

	Tiles.Add(TileManager->GetTileAtLocation(Religion->GetActorLocation()));

	while (Tiles.Num() > 0)
	{
		ATile* CurrentTile = Tiles.Pop(false);

		if (CurrentTile->HasConflictingReligion(Religion))
			return CurrentTile;

		for (auto AdjacentTile : TileManager->GetAdjacentTiles(CurrentTile))
		{
			if (!CheckedTiles.Contains(AdjacentTile))
				Tiles.Add(AdjacentTile);
		}

		CheckedTiles.Add(CurrentTile);
	}

	return nullptr;
}

ATile* AReligionManager::CalculateNearestEmptyTile(AReligion* Religion)
{
	TArray<ATile*> Tiles;
	TArray<ATile*> CheckedTiles;

	Tiles.Add(TileManager->GetTileAtLocation(Religion->GetActorLocation()));

	while (Tiles.Num() > 0)
	{
		ATile* CurrentTile = Tiles.Pop(false);

		if (CurrentTile->GetPopulationOfReligion(Religion) == 0)
			return CurrentTile;

		for (auto AdjacentTile : TileManager->GetAdjacentTiles(CurrentTile))
		{
			if (!CheckedTiles.Contains(AdjacentTile))
				Tiles.Add(AdjacentTile);
		}

		CheckedTiles.Add(CurrentTile);
	}

	return nullptr;
}

