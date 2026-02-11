// Copyright Epic Games, Inc. All Rights Reserved.

#include "HeroCharacter.h"
#include "NoiseComponent.h"

AHeroCharacter::AHeroCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	NoiseComponent = CreateDefaultSubobject<UNoiseComponent>(TEXT("NoiseComponent"));
}

void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHeroCharacter::Attack()
{
	if (UNoiseComponent* NoiseComp = FindComponentByClass<UNoiseComponent>())
	{
		float NoiseToMake = (HeroClass == EHeroClass::Thief) ? 2.0f : 15.0f;
		NoiseComp->AddNoise(NoiseToMake);
	}
}
