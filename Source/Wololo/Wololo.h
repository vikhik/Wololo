// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#ifndef __WOLOLO_H__
#define __WOLOLO_H__

#include "EngineMinimal.h"
#include "Engine.h"

DECLARE_LOG_CATEGORY_EXTERN(LogWololo, Log, All);

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)


#endif
