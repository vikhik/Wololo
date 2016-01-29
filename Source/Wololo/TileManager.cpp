// Fill out your copyright notice in the Description page of Project Settings.

#include "Wololo.h"
#include "TileManager.h"


// Sets default values
ATileManager::ATileManager() : 
	TownSpawnChance(0.1f),
	Height(500),
	Width(500),
	TilesHigh(10),
	TilesWide(10)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

void ATileManager::SpawnThings()
{
	float TileHeight = Height / TilesHigh;
	float TileWidth = Width / TilesWide;

	float MinHeight = TileHeight * TilesHigh * 0.5;
}

