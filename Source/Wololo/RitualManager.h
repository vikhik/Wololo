// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RitualData.h"

class WOLOLO_API RitualManager
{
private:	
	RitualManager();

protected:
	static RitualManager *instance;

public:
	static RitualManager *GetInstance();
	static void Destroy();

	TMap<ERitualType, FRitualData> RitualMap;
};
