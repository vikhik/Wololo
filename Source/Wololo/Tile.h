// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Town.h"
#include "Religion.h"
#include "Tile.generated.h"

UCLASS()
class WOLOLO_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Height;

	UFUNCTION(BlueprintPure, Category = "Tiles")
		bool HasConflictingReligion(AReligion* Religion);

	UFUNCTION(BlueprintPure, Category = "Tiles")
		bool IsEmpty();

	UFUNCTION(BlueprintPure, Category = "Tiles")
		TArray<AReligion*> GetReligions();

	UFUNCTION(BlueprintPure, Category = "Tiles")
		float GetReligiousPercentage(AReligion* Religion);

	UFUNCTION(BlueprintPure, Category = "Tiles")
		int32 GetPopulation();

	UFUNCTION(BlueprintPure, Category = "Tiles")
		int32 GetPopulationOfReligion(AReligion* Religion);

	UFUNCTION(BlueprintCallable, Category = "Tiles")
		void AddPopulation(AReligion* Religion, int32 AddedPop);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ATown* Town; // may be nullptr

	UFUNCTION(BlueprintCallable, Category = "Tiles")
		void SetWidthAndHeight(float NewWidth, float NewHeight);

	TMap<AReligion*, int32> GetPopulationByReligion();

	void Attack(AReligion* Religion, AReligion* TargetReligion);
	void Convert(AReligion* Religion);
	void MovePopulation(ATile* EnemyTile, AReligion* Religion, float Ratio);
	void Grow(AReligion* Religion);
	static float ConversionRate;
private:
	TMap<AReligion*, int32> Population;
};
