// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Tile.h"
#include "Town.h"
#include "TileManager.generated.h"

UCLASS()
class WOLOLO_API ATileManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Height;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 TilesWide;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 TilesHigh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TownSpawnChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SpawnZ;

	UFUNCTION(BlueprintCallable, Category = "Tiles")
		void SpawnTilesAndTowns();

	UFUNCTION(BlueprintCallable, Category = "Tiles")
		ATile* GetTileInDirection(ATile* Source, ATile* Target);

	UFUNCTION(BlueprintCallable, Category = "Tiles")
		ATile* GetTileAtLocation(FVector Location);

	UFUNCTION(BlueprintCallable, Category = "Tiles")
		TArray<ATile*> GetAdjacentTiles(ATile* Tile);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ATile*> Tiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ATile*> TilesWithTowns;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ATile> TileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ATown> TownClass;

	UFUNCTION(BlueprintCallable, Category = "Tiles")
		ATile* SpawnTileAtLocation(FVector Location);

	UFUNCTION(BlueprintCallable, Category = "Tiles")
		ATown* SpawnTownAtTile(ATile* Tile);
private:
	float TileHeight;
	float TileWidth;

	float MaxY;
	float MaxX;
};
