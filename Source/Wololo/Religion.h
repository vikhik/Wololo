// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Religion.generated.h"

UENUM()
enum class EReligionType : uint8
{
	Aggressive, // Rock
	Communal, // Paper
	Meditiative, // Scissors
	MAX 
};

UCLASS()
class WOLOLO_API AReligion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AReligion();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FColor Color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 NumberOfFollowers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<float> TypeInfluences; // 0.0 - 1.0

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EReligionType CurrentType;

	UFUNCTION(BlueprintCallable, Category = "Religion")
		void SetNewType(EReligionType Type);
};
