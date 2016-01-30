
#pragma once

#include "GameFramework/Actor.h"
#include "RitualData.generated.h"

UENUM()
enum class ERitualType : uint8
{
	Aggressive, // Rock
	Communal, // Paper
	Meditiative, // Scissors
	MAX
};