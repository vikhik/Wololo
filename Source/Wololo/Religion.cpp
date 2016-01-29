// Fill out your copyright notice in the Description page of Project Settings.

#include "Wololo.h"
#include "Religion.h"


// Sets default values
AReligion::AReligion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NumberOfFollowers = 1000;

	TypeInfluences.SetNum((uint8)EReligionType::MAX);

	TypeInfluences[(uint8)CurrentType] = 1.0;
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

