// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RitualData.h"
#include "Religion.generated.h"

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

	// TRAIT VALUES

	UFUNCTION(BlueprintPure, Category = "Religion")
		float GetAttackRate() const;

	UFUNCTION(BlueprintPure, Category = "Religion")
		float GetMoveRate() const;

	UFUNCTION(BlueprintPure, Category = "Religion")
		float GetMoveKeep() const;

	UFUNCTION(BlueprintPure, Category = "Religion")
		float GetGrowthRate() const;

	UFUNCTION(BlueprintPure, Category = "Religion")
		int32 GetGrowthCap();

	UFUNCTION(BlueprintPure, Category = "Religion")
		ERitualType GetHighestRitualType() const;

	// Other stuff

	TMap<ERitualType, float> RitualInfluences; // 0.0 - 1.0

	UFUNCTION(BlueprintPure, Category = "Religion")
		float GetAggressiveInfluence() const;

	UFUNCTION(BlueprintPure, Category = "Religion")
		float GetCommunalInfluence() const;

	UFUNCTION(BlueprintPure, Category = "Religion")
		float GetMeditativeInfluence() const;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FColor Color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Followers;

	UFUNCTION(BlueprintCallable, Category = "Religion")
		void SetRitualInfluences(float AggressiveInfluence, float CommunalInfluence, float MeditativeInfluence);

	// COMPLETELY OVERRIDE EXISTING RITUALS
	UFUNCTION(BlueprintCallable, Category = "Religion")
		void SetNewType(ERitualType Type);

	void UpdateRitualData();

	TSet<AActor*> OwnedTiles;
	TSet<AActor*> BorderTiles;
	AActor* BaseTile;

private:
	void CleanUpInfluences();

	void SetFromVec(FVector ToUse);
};
