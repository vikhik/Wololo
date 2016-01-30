// Fill out your copyright notice in the Description page of Project Settings.

#include "Wololo.h"
#include "TileManager.h"


// Sets default values
ATileManager::ATileManager() : 
	TownSpawnChance(0.1f),
	Height(3000.0),
	Width(3000.0),
	TilesHigh(30),
	TilesWide(30),
	SpawnZ(20)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TileClass = ATile::StaticClass();
}

// Called when the game starts or when spawned
void ATileManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATileManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ATileManager::SpawnTilesAndTowns()
{
	TileHeight = Height / TilesHigh; // 100
	TileWidth = Width / TilesWide; // 100

	MaxY = (TileHeight * TilesHigh * 0.5) - TileHeight * 0.5; // 1450
	MaxX = (TileWidth * TilesWide * 0.5) - TileHeight * 0.5; // 1450

	for (float y = -MaxY; y <= MaxY; y += TileHeight) // [-1450, 1450]
	{
		for (float x = -MaxX; x <= MaxX; x += TileHeight)
		{
			FVector Pos = FVector(x, y, SpawnZ);

			ATile* NewTile = SpawnTileAtLocation(Pos);

			float DieRoll = FMath::FRand();

			if (DieRoll < TownSpawnChance)
			{
				NewTile->Town = SpawnTownAtTile(NewTile);
			}
		}
	}
}

ATile* ATileManager::SpawnTileAtLocation(FVector Location)
{
	UWorld* World = GetWorld();

	ATile* NewTile = (ATile*)World->SpawnActor(TileClass, &Location);

	NewTile->SetWidthAndHeight(TileWidth, TileHeight);

	Tiles.Add(NewTile);

	return NewTile;
}

ATile* ATileManager::GetTileAtLocation(FVector Location)
{
	for (ATile* Tile : Tiles)
	{
		FVector TileLocation = Tile->GetActorLocation();

		float xdiff = FMath::Abs(TileLocation.X - Location.X);
		float ydiff = FMath::Abs(TileLocation.Y - Location.Y);

		if (xdiff < Tile->Width && ydiff < Tile->Height)
		{
			return Tile;
		}
	}

	return nullptr;
}

TArray<ATile*> ATileManager::GetAdjacentTiles(ATile* Tile)
{
	TArray<ATile*> Tiles;

	FVector Location = Tile->GetActorLocation();
	FVector AdjustedLocation;

	if (Location.X > -MaxX)
	{
		AdjustedLocation = Location;
		AdjustedLocation.X -= TileWidth;
		Tiles.Add(GetTileAtLocation(AdjustedLocation));
	}

	if (Location.X < MaxX)
	{
		AdjustedLocation = Location;
		AdjustedLocation.X += TileWidth;
		Tiles.Add(GetTileAtLocation(AdjustedLocation));
	}

	if (Location.Y > -MaxY)
	{
		AdjustedLocation = Location;
		AdjustedLocation.Y -= TileHeight;
		Tiles.Add(GetTileAtLocation(AdjustedLocation));
	}

	if (Location.Y < MaxY)
	{
		AdjustedLocation = Location;
		AdjustedLocation.Y += TileHeight;
		Tiles.Add(GetTileAtLocation(AdjustedLocation));
	}

	return Tiles;
}

ATown* ATileManager::SpawnTownAtTile(ATile* Tile)
{
	UWorld* World = GetWorld();

	FVector Loc = Tile->GetActorLocation();

	ATown* NewTown = (ATown*)World->SpawnActor(TownClass, &Loc);

	TilesWithTowns.Add(Tile);

	return NewTown;
}

