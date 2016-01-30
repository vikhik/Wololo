// Fill out your copyright notice in the Description page of Project Settings.

#include "Wololo.h"
#include "RitualManager.h"

RitualManager* RitualManager::instance;

RitualManager::RitualManager()
{

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
