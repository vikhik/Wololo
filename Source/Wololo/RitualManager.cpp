// Fill out your copyright notice in the Description page of Project Settings.

#include "Wololo.h"
#include "RitualManager.h"

RitualManager* RitualManager::instance;

RitualManager::RitualManager()
{
	// Aggro > Meditative, Meditative > Communal, Communal > Aggro

	RitualMap.Add(ERitualType::Aggressive, 
		FRitualData(
			0.6f,	// Spread Minimum Percentage requirement (How much of a tile we need control before we spread)
			200,	// Spread Minimum Population requirement
			0.5f,	// Spread Rate (how much of the current population MOVES to the next tile)
			0.05f,	// Growth Rate (Compound interest on Population)
			2000,	// Growth Max
			5.0f,	// Conflict Offense (% of population that potentially kill)
			0.5f,	// Conflict Defense (% of population that ignores kills)
			0.15f	// Conflict Conversion (% of pop converted from the enemy)
			));

	RitualMap.Add(ERitualType::Communal, 
		FRitualData(
			0.7f,
			800, 
			0.3f, 
			0.02f, 
			6000,
			2.0f, 
			2.0f,
			0.2f
			));

	RitualMap.Add(ERitualType::Meditiative, 
		FRitualData(
			0.8f,
			500,
			0.2f, 
			0.035f, 
			4000,
			2.0f, 
			3.0f,
			0.1f
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
