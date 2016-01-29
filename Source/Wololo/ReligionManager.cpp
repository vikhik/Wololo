// Fill out your copyright notice in the Description page of Project Settings.

#include "Wololo.h"
#include "ReligionManager.h"


// Sets default values
AReligionManager::AReligionManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ReligionClass = AReligion::StaticClass();
}

// Called when the game starts or when spawned
void AReligionManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AReligionManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	//for (auto Religion : AllReligions)
	//{

	//}
}

void AReligionManager::SpawnInitialReligions(int32 Num)
{
	UWorld* World = GetWorld();

	FTransform ZeroTransform;

	uint8 Type = 0;

	for (uint8 i = 0; i < Num; i++)
	{
		AReligion* NewReligion = (AReligion*) World->SpawnActor(ReligionClass, &FVector::ZeroVector);

		NewReligion->SetNewType((EReligionType)Type);

		Type++;

		if ((EReligionType)Type == EReligionType::MAX)
		{
			Type = 0;
		}

		AllReligions.Add(NewReligion);
	}
}

