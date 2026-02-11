// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NoiseComponent.h"
#include "S_HeroData.h"
#include "HeroCharacter.generated.h"

UCLASS()
class MYPROJECT_API AHeroCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AHeroCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero")
	EHeroClass HeroClass = EHeroClass::Fighter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hero")
	class UNoiseComponent* NoiseComponent;

	UFUNCTION(BlueprintCallable, Category = "Hero")
	void Attack();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual void Tick(float DeltaTime) override;
};
