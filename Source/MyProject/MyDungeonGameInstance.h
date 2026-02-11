// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "S_HeroData.h"
#include "MyDungeonGameInstance.generated.h"

UCLASS()
class MYPROJECT_API UMyDungeonGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Game")
	TArray<FHeroData> PartySlots;

	UPROPERTY(BlueprintReadWrite, Category = "Game")
	int32 CurrentHeroIndex = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Game")
	FVector LastDeathLocation = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite, Category = "Game")
	FHeroData FallenHeroData;
};
