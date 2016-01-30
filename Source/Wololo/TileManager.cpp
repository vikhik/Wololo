// Fill out your copyright notice in the Description page of Project Settings.

#include "Wololo.h"
#include "TileManager.h"


// Sets default values
ATileManager::ATileManager() : 
	TownSpawnChance(0.1f),
	Height(500),
	Width(500),
	TilesHigh(10),
	TilesWide(10),
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
	TileHeight = Height / TilesHigh; // 50
	TileWidth = Width / TilesWide; // 50

	float MaxY = (TileHeight * TilesHigh * 0.5); // 250
	float MaxX = (TileWidth * TilesWide * 0.5); // 250

	for (float y = -MaxY; y < MaxY; y += TileHeight)
	{
		for (float x = -MaxX; x < MaxX; x += TileHeight)
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

ATown* ATileManager::SpawnTownAtTile(ATile* Tile)
{
	UWorld* World = GetWorld();

	FVector Loc = Tile->GetActorLocation();

	ATown* NewTown = (ATown*)World->SpawnActor(TownClass, &Loc);

	TilesWithTowns.Add(Tile);

	return NewTown;
}

