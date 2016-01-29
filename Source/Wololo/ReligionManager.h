// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Religion.h"
#include "ReligionManager.generated.h"

UCLASS()
class WOLOLO_API AReligionManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AReligionManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* ReligionClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AReligion*> AllReligions;

	UFUNCTION(BlueprintCallable, Category = "Religion")
		void SpawnInitialReligions(int32 Num);
};
