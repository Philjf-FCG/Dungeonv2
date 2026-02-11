// Copyright Epic Games, Inc. All Rights Reserved.

#include "NoiseComponent.h"

UNoiseComponent::UNoiseComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	NoiseLevel = 0.0f;
}

void UNoiseComponent::AddNoise(float Amount)
{
	NoiseLevel = FMath::Clamp(NoiseLevel + Amount, 0.0f, MaxNoiseThreshold + 1.0f);
	if (NoiseLevel >= MaxNoiseThreshold)
	{
		OnNoiseThresholdReached.Broadcast();
	}
}

void UNoiseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (NoiseLevel > 0.0f)
	{
		NoiseLevel -= DecayRate * DeltaTime;
		if (NoiseLevel < 0.0f)
		{
			NoiseLevel = 0.0f;
		}
	}
}
