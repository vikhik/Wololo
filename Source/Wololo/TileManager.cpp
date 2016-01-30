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
	MaxX = (TileWidth * TilesWide * 0.5) - TileWidth * 0.5; // 1450

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

ATile* ATileManager::GetTileInDirection(ATile* Source, ATile* Target)
{
	FVector SourceLoc = Source->GetActorLocation();
	FVector TargetLoc = Target->GetActorLocation();

	float xdiff = TargetLoc.X - SourceLoc.X;
	float ydiff = TargetLoc.Y - SourceLoc.Y;

	FVector ReturnTileLocation = SourceLoc;

	if (FMath::Abs(xdiff) > FMath::Abs(ydiff))
	{
		if (xdiff > 0)
		{
			ReturnTileLocation.X += TileWidth;
		}
		else
		{
			ReturnTileLocation.X -= TileWidth;
		}
	}
	else
	{
		if (ydiff > 0)
		{
			ReturnTileLocation.Y += TileHeight;
		}
		else
		{
			ReturnTileLocation.Y -= TileHeight;
		}
	}

	auto ReturnTile = GetTileAtLocation(ReturnTileLocation);

	return ReturnTile;
}

ATile* ATileManager::SpawnTileAtLocation(FVector Location)
{
	UWorld* World = GetWorld();

	ATile* NewTile = (ATile*)World->SpawnActor(TileClass, &Location);

	NewTile->SetWidthAndHeight(TileWidth, TileHeight);

	Tiles.Add(NewTile);

	return NewTile;
}

ATileManager::TileIndexPair ATileManager::GetTileIndex(FVector Location)
{
  ATileManager::TileIndexPair iPair;

  // If out of bounds return null
  if (Location.X < -MaxX || Location.X > MaxX ||
      Location.Y < -MaxY || Location.Y > MaxY)
    {
      iPair.indexX = -1;
      iPair.indexY = -1;
    }
  else
    {
      float newX = Location.X + MaxX;
      newX /= TileWidth;
      //newX -= 0.5f;
      iPair.indexX = (int32)newX;

      float newY = Location.Y + MaxY;
      newY /= TileHeight;
      //newY -= 0.5f;
      iPair.indexY = (int32)newY;
    }
  return iPair;
}

ATile* ATileManager::GetTileAtLocation(FVector Location)
{
  ATileManager::TileIndexPair iPair = GetTileIndex(Location);
  // If out of bounds return null
  if (iPair.indexX == -1 || iPair.indexY == -1)
    return nullptr;

  int32 tileIndex = iPair.indexY * TilesWide + iPair.indexX;
  if (tileIndex > Tiles.Num() || tileIndex < 0)
    return nullptr;
  
  return Tiles[tileIndex];
}

TArray<ATile*> ATileManager::GetAdjacentTiles(ATile* Tile)
{
	if (Tile->Neighbours.Num() > 0)
		return Tile->Neighbours;

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

	Tile->Neighbours = Tiles;

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

