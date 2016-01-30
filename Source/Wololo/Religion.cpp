// Fill out your copyright notice in the Description page of Project Settings.

#include "Wololo.h"
#include "Religion.h"


// Sets default values
AReligion::AReligion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Followers = 1000;
}

// Called when the game starts or when spawned
void AReligion::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AReligion::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

float AReligion::GetAttackRate() const
{
	switch (GetHighestRitualType())
	{
	case ERitualType::Aggressive:
		return 2.f / 3.f;
	case ERitualType::Communal:
		return 1.f / 3.f;
	case ERitualType::Meditiative:
		return 0;
	}
	return 2.f / 3.f;
}

float AReligion::GetMoveRate() const
{
	switch (GetHighestRitualType())
	{
	case ERitualType::Aggressive:
	case ERitualType::Communal:
		return 2.f / 3.f;
	case ERitualType::Meditiative:
		return 1.f / 3.f;
	}
	return 1.f / 2.f;
}

float AReligion::GetMoveKeep() const
{
	switch (GetHighestRitualType())
	{
	case ERitualType::Aggressive:
		return 100;
	case ERitualType::Communal:
		return 50;
	case ERitualType::Meditiative:
		return 300;
	}
	return 200;
}

float AReligion::GetGrowthRate() const
{
	switch (GetHighestRitualType())
	{
	case ERitualType::Meditiative:
		return 1.f / 10.f;
	case ERitualType::Aggressive:
		return 1.f / 11.f;
	case ERitualType::Communal:
		return 1.f / 12.f;
	}
	return 1.f / 10.f;
}

ERitualType AReligion::GetHighestRitualType() const
{
	float Aggro = GetAggressiveInfluence();
	float Comms = GetCommunalInfluence();
	float Meds = GetMeditativeInfluence();

	if (Aggro > Comms && Aggro > Meds)
		return ERitualType::Aggressive;
	else if (Comms > Aggro && Comms > Meds)
		return ERitualType::Communal;
	else
		return ERitualType::Meditiative;
}

float AReligion::GetAggressiveInfluence() const
{
	if (!RitualInfluences.Contains(ERitualType::Aggressive))
		return 0;
	return RitualInfluences[ERitualType::Aggressive];
}

float AReligion::GetCommunalInfluence() const
{
	if (!RitualInfluences.Contains(ERitualType::Communal))
		return 0;
	return RitualInfluences[ERitualType::Communal];
}

float AReligion::GetMeditativeInfluence() const
{
	if (!RitualInfluences.Contains(ERitualType::Meditiative))
		return 0;
	return RitualInfluences[ERitualType::Meditiative];
}

void AReligion::SetRitualInfluences(float AggressiveInfluence, float CommunalInfluence, float MeditativeInfluence)
{
	RitualInfluences.Empty();

	RitualInfluences.Add(ERitualType::Aggressive, AggressiveInfluence);
	RitualInfluences.Add(ERitualType::Communal, CommunalInfluence);
	RitualInfluences.Add(ERitualType::Meditiative, MeditativeInfluence);

	UpdateRitualData();
}

void AReligion::SetNewType(ERitualType Type)
{
	RitualInfluences.Empty();

	RitualInfluences.Add(Type);

	RitualInfluences[Type] = 1.0f;

	UpdateRitualData();
}

void AReligion::UpdateRitualData()
{
	CleanUpInfluences();
}

void AReligion::CleanUpInfluences()
{
	FVector VectorRep = FVector(GetAggressiveInfluence(), GetCommunalInfluence(), GetMeditativeInfluence());

	VectorRep.Normalize();

	SetFromVec(VectorRep);
}

void AReligion::SetFromVec(FVector ToUse)
{
	RitualInfluences.Empty();

	RitualInfluences.Add(ERitualType::Aggressive, ToUse.X);
	RitualInfluences.Add(ERitualType::Communal, ToUse.Y);
	RitualInfluences.Add(ERitualType::Meditiative, ToUse.Z);
}

int32 AReligion::GetGrowthCap()
{
	return 5000;
}

