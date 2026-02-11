// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "S_HeroData.h"
#include "DungeonGameMode.generated.h"

/**
 * ADungeonGameMode
 * Handles the "First Playable" loop: Hero Spawning, Death Persistence, and Shushing.
 */
UCLASS()
class MYPROJECT_API ADungeonGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADungeonGameMode();

	// --- Core Gameplay Loop ---

	/** Selects the next living hero from the GameInstance and spawns them */
	UFUNCTION(BlueprintCallable, Category = "Dungeon | Flow")
	void SpawnNextHero();

	/** Called when a hero dies or is caught by the Behearer */
	UFUNCTION(BlueprintCallable, Category = "Dungeon | Flow")
	void OnHeroDied(FVector DeathLocation, FHeroData HeroData);

	/** Spawns the Behearer and kills the player for being too loud */
	UFUNCTION(BlueprintCallable, Category = "Dungeon | Mechanics")
	void HandleShush(AActor* LoudActor);

protected:
	/** Called when the game starts or when in transition */
	virtual void BeginPlay() override;

	// --- Configuration: Assign these in the Editor ---

	/** The Blueprint class for the 'Ghost' or 'Corpse' left by fallen heroes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon | Classes")
	TSubclassOf<AActor> CorpseClass;

	/** The Behearer actor (Big floating ear monster) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon | Classes")
	TSubclassOf<AActor> BehearerClass;

	/** The sound effect played when the Behearer catches you */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon | Audio")
	class USoundBase* ShushSound;

	/** Reference to a PlayerStart or Entrance point in the map */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon | Setup")
	FName EntranceTag = FName("DungeonEntrance");

private:
	/** Internal helper to find the GameInstance cast to our custom type */
	class UMyDungeonGameInstance* GetDungeonGI() const;
};
