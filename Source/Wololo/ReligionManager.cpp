// Fill out your copyright notice in the Description page of Project Settings.

#include "Wololo.h"
#include "ReligionManager.h"

// Sets default values
AReligionManager::AReligionManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ReligionClass = AReligion::StaticClass();
	TownClass = ATown::StaticClass();
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

void AReligionManager::SpawnReligionAtLocation(FVector Location, EReligionType Type)
{
	UWorld* World = GetWorld();

	AReligion* NewReligion = (AReligion*)World->SpawnActor(ReligionClass, &Location);

	NewReligion->SetNewType(Type);

	AllReligions.Add(NewReligion);
}

void AReligionManager::SpawnNumberReligions(int32 Num)
{
	FTransform ZeroTransform;

	uint8 Type = 0;

	for (uint8 i = 0; i < Num; i++)
	{
		SpawnReligionAtLocation(FVector::ZeroVector, (EReligionType)Type);

		Type++;

		if ((EReligionType)Type == EReligionType::MAX)
		{
			Type = 0;
		}
	}
}

void AReligionManager::SpawnReligionInEveryTown()
{
	UWorld* World = GetWorld();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(World, TownClass, FoundActors);

	SpawnNumberReligions(FoundActors.Num());

	int i = 0;

	for (AReligion* Religion : AllReligions)
	{
		Religion->SetActorLocation(FoundActors[i]->GetActorLocation());
		i++;

		if (i > FoundActors.Num())
			i = 0;
	}
}

