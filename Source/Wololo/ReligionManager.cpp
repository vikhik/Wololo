// Fill out your copyright notice in the Description page of Project Settings.

#include "Wololo.h"
#include "ReligionManager.h"

// Sets default values
AReligionManager::AReligionManager() :
	BasePopulation(250),
	PopulationVariance(100)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ReligionClass = AReligion::StaticClass();
	TownClass = ATown::StaticClass();

	Colors.Add(FColor::FromHex("B21212"));
	Colors.Add(FColor::FromHex("FFFC19"));
	Colors.Add(FColor::FromHex("FF0000"));
	Colors.Add(FColor::FromHex("1485CC"));
	Colors.Add(FColor::FromHex("12B212"));
	Colors.Add(FColor::FromHex("4319FF"));
	Colors.Add(FColor::FromHex("00FF00"));
	Colors.Add(FColor::FromHex("CC6514"));
}

// Called when the game starts or when spawned
void AReligionManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (!TileManager)
	{
		TSubclassOf<ATileManager> ClassToFind = ATileManager::StaticClass();
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, FoundActors);

		if (FoundActors.Num() > 0)
			TileManager = (ATileManager*)FoundActors[0];
	}
}

// Called every frame
void AReligionManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
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

	TArray<ATile*> TilesWithTowns = TileManager->TilesWithTowns;

	SpawnNumberReligions(TilesWithTowns.Num());

	int i = 0;

	for (AReligion* Religion : AllReligions)
	{
		Religion->SetActorLocation(TilesWithTowns[i]->GetActorLocation());

		int32 RandomPop = BasePopulation + FMath::FRandRange(-PopulationVariance, PopulationVariance);

		((ATile*)TilesWithTowns[i])->AddPopulation(Religion, RandomPop);

		Religion->NumberOfFollowers = RandomPop; // TODO proper updating

		if (i >= Colors.Num())
		{
			Colors.Add(GenerateNewColor());
		}
		
		Religion->Color = Colors[i];

		i++;
		if (i >= TilesWithTowns.Num())
			return; // ERROR LATER, EXIT FOR NOW
	}
}

FColor AReligionManager::GenerateNewColor()
{
	FVector RandVec = FMath::VRand();
	FColor NewColor = FLinearColor(RandVec).ToFColor(false);

	return NewColor;
}

