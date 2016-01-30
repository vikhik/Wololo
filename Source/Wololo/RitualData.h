
#pragma once

#include "GameFramework/Actor.h"
#include "RitualData.generated.h"

USTRUCT(BlueprintType)
struct FRitualData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SpreadMinimumPercentage = 0.8f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 SpreadMinimumPopulation = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SpreadRate = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float GrowthRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 GrowthMax = 5000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ConflictOffense = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ConflictDefense = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ConflictConversion = 0.1f;

	FRitualData(
		float SpreadMinPercentage = 0.8f,
		int32 SpreadMinPop = 200,
		float SpreadRatePercentage = 0.2f,
		float GrowthRatePercentage = 0.1f,
		int32 GrowthMaxPop = 5000,
		float ConflictOffensePercentage = 0.1f,
		float ConflictDefensePercentage = 0.1f,
		float ConflictConversionPercentage = 0.1f) :
		SpreadMinimumPercentage(SpreadMinPercentage),
		SpreadMinimumPopulation(SpreadMinPop),
		SpreadRate(SpreadRatePercentage),
		GrowthRate(GrowthRatePercentage),
		GrowthMax(GrowthMaxPop),
		ConflictOffense(ConflictOffensePercentage),
		ConflictDefense(ConflictDefensePercentage),
		ConflictConversion(ConflictConversionPercentage)
	{

	}

	void Zero()
	{
		SpreadMinimumPercentage = 0;
		SpreadMinimumPopulation = 0;
		SpreadRate = 0;
		GrowthRate = 0;
		GrowthMax = 0;
		ConflictOffense = 0;
		ConflictDefense = 0;
		ConflictConversion = 0;
	}

	void Add(FRitualData RitualData, float Influence)
	{
		SpreadMinimumPercentage += RitualData.SpreadMinimumPercentage* Influence;
		SpreadMinimumPopulation += RitualData.SpreadMinimumPopulation* Influence;
		SpreadRate				+= RitualData.SpreadRate				* Influence;
		GrowthRate				+= RitualData.GrowthRate				* Influence;
		GrowthMax				+= RitualData.GrowthMax				* Influence;
		ConflictOffense			+= RitualData.ConflictOffense		* Influence;
		ConflictDefense			+= RitualData.ConflictDefense		* Influence;
		ConflictConversion		+= RitualData.ConflictConversion		* Influence;
	}
};

UENUM()
enum class ERitualType : uint8
{
	Aggressive, // Rock
	Communal, // Paper
	Meditiative, // Scissors
	MAX
};