// Fill out your copyright notice in the Description page of Project Settings.

#include "Wololo.h"
#include "RitualManager.h"

RitualManager* RitualManager::instance;

RitualManager::RitualManager()
{
	// Aggressive - Expand Fast, Grow Slowly, High Attack, Low Defense
	RitualMap.Add(ERitualType::Aggressive, FRitualData(0.5f, 100, 0.5f, 0.05f, 0.5f, 0.0f));

	// Communal - Expand Slowly, Grow Fast, Medium Attack, Medium Defense
	RitualMap.Add(ERitualType::Communal, FRitualData(0.8f, 300, 0.3f, 0.2f, 0.2f, 0.1f));

	// Meditative - Expand Slowly, Grow Slowly, Low Attack, High Defense
	RitualMap.Add(ERitualType::Meditiative, FRitualData(0.9f, 500, 0.2f, 0.1f, 0.1f, 0.5f));
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
