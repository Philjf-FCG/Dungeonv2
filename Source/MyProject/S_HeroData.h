// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "S_HeroData.generated.h"

UENUM(BlueprintType)
enum class EHeroClass : uint8
{
	Fighter UMETA(DisplayName = "Fighter"),
	Cleric UMETA(DisplayName = "Cleric"),
	Thief UMETA(DisplayName = "Thief"),
	AccountingWizard UMETA(DisplayName = "Accounting Wizard")
};

USTRUCT(BlueprintType)
struct FHeroData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero")
	FText HeroName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero")
	EHeroClass ClassType = EHeroClass::Fighter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero")
	TSubclassOf<APawn> HeroBlueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero")
	bool bIsDead = false;
};
