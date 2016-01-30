// Fill out your copyright notice in the Description page of Project Settings.

#include "Wololo.h"
#include "RitualManager.h"

RitualManager* RitualManager::instance;

RitualManager::RitualManager()
{
	// Aggro > Meditative, Meditative > Communal, Communal > Aggro

	// Aggressive - Expand Fast, Grow Slowly, High Attack, Low Defense
	RitualMap.Add(ERitualType::Aggressive, 
		FRitualData(
			0.7f,	// Spread Minimum Percentage requirement (How much of a tile we need control before we spread)
			500,	// Spread Minimum Population requirement
			0.4f,	// Spread Rate (how much of the current population MOVES to the next tile)
			0.20f,	// Growth Rate (Compound interest on Population)
			0.6f,	// Conflict Offense (% of population that potentially kill)
			0.0f,	// Conflict Defense (% of population that ignores kills)
			0.0f	// Conflict Conversion (% of pop converted from the enemy)
			));

	// Communal - Expand Slowly, Grow Fast, Medium Attack, Medium Defense
	RitualMap.Add(ERitualType::Communal, 
		FRitualData(
			0.8f,
			700, 
			0.3f, 
			0.30f, 
			0.0f, 
			0.0f,
			0.6f
			));

	// Meditative - Expand Slowly, Grow Slowly, Low Attack, High Defense
	RitualMap.Add(ERitualType::Meditiative, 
		FRitualData(
			0.9f,
			300,
			0.2f, 
			0.25f, 
			0.0f, 
			0.6f,
			0.0f
			));
}

RitualManager *RitualManager::GetInstance()
{
	if (!instance)
	{
		instance = new RitualManager();
	}
	return instance;
}

void RitualManager::Destroy()
{
	delete instance;
}
