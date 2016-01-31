// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Religion.h"
#include "TileManager.h"
#include "ReligionManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerWon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerLost, AReligion*, LostReligion);

UCLASS()
class WOLOLO_API AReligionManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AReligionManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(BlueprintAssignable)
		FPlayerWon OnPlayerWon;

	UPROPERTY(BlueprintAssignable)
		FPlayerLost OnPlayerLost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FColor> Colors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 BasePopulation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 PopulationVariance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ATown> TownClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AReligion> ReligionClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AReligion*> AllReligions;

	UFUNCTION(BlueprintCallable, Category = "Religion")
		void SpawnReligionAtLocation(FVector Location, ERitualType Type);

	UFUNCTION(BlueprintCallable, Category = "Religion")
		void SpawnNumberReligions(int32 Num);

	UFUNCTION(BlueprintCallable, Category = "Religion")
		void SpawnReligionInEveryTown();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ATileManager* TileManager;

	UFUNCTION(BlueprintCallable, Category = "Religion")
		void RunUpdate();

	void ConsiderAndDoAttack(ATile* Tile, AReligion* Religion, ERitualType RitualType);

private:
	FColor GenerateNewColor();
	ATile* CalculateNearestEnemyTile(ATile* Tile, AReligion* Religion);
	ATile* CalculateNearestEmptyTile(ATile* Tile, AReligion* Religion);

	TSet<ATile*> EmptyTiles;

	bool TargetIsValid(ATile* TargetTile, AReligion* Religion, ERitualType RitualType);
};
