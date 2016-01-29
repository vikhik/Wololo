// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Tile.h"
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

	UFUNCTION(BlueprintCallable, Category = "Tiles")
		void SpawnThings();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ATile*> Tiles;
};
