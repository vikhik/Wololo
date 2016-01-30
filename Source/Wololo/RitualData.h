
#pragma once

#include "GameFramework/Actor.h"
#include "RitualData.generated.h"

USTRUCT()
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
		float ConflictOffense = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ConflictDefense = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float GrowthRate = 0.1f;

	FRitualData(
		float SpreadMinPercentage = 0.8f,
		int32 SpreadMinPop = 200,
		float SpreadRatePercentage = 0.2f,
		float GrowthRatePercentage = 0.1f,
		float ConflictOffensePercentage = 0.2f,
		float ConflictDefensePercentage = 0.1f) :
		SpreadMinimumPercentage(SpreadMinPercentage),
		SpreadMinimumPopulation(SpreadMinPop),
		SpreadRate(SpreadRatePercentage),
		GrowthRate(GrowthRatePercentage),
		ConflictOffense(ConflictOffensePercentage),
		ConflictDefense(ConflictDefensePercentage)
	{

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