// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NoiseComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNoiseTriggered);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MYPROJECT_API UNoiseComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNoiseComponent();

	UPROPERTY(BlueprintAssignable)
	FOnNoiseTriggered OnNoiseThresholdReached;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise")
	float DecayRate = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise")
	float MaxNoiseThreshold = 100.0f;

	UFUNCTION(BlueprintCallable, Category = "Noise")
	void AddNoise(float Amount);

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float NoiseLevel;
};
