// Copyright Epic Games, Inc. All Rights Reserved.

#include "DungeonGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "MyDungeonGameInstance.h"

ADungeonGameMode::ADungeonGameMode()
{
}

void ADungeonGameMode::SpawnNextHero()
{
	UMyDungeonGameInstance* GI = Cast<UMyDungeonGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GI || !GI->PartySlots.IsValidIndex(GI->CurrentHeroIndex))
	{
		return;
	}

	FHeroData& ActiveHero = GI->PartySlots[GI->CurrentHeroIndex];

	// 1. Spawn the Hero
	FActorSpawnParameters SpawnParams;
	AActor* StartPoint = FindPlayerStart(GetWorld()->GetFirstPlayerController());
	
	APawn* NewHero = GetWorld()->SpawnActor<APawn>(
		ActiveHero.HeroBlueprint, 
		StartPoint->GetActorLocation(), 
		StartPoint->GetActorRotation(), 
		SpawnParams
	);

	if (NewHero)
	{
		GetWorld()->GetFirstPlayerController()->Possess(NewHero);
	}

	// 2. Spawn the "Mess" left by the previous run
	if (!GI->LastDeathLocation.IsZero())
	{
		// Spawn a corpse actor for potential resurrection/looting
		AActor* Corpse = GetWorld()->SpawnActor<AActor>(
			CorpseClass, 
			GI->LastDeathLocation, 
			FRotator::ZeroRotator
		);
	}
}

void ADungeonGameMode::OnHeroDied(FVector DeathLocation, FHeroData HeroData)
{
	UMyDungeonGameInstance* GI = Cast<UMyDungeonGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		GI->LastDeathLocation = DeathLocation;
		GI->FallenHeroData = HeroData;
		GI->CurrentHeroIndex++;
		
		UGameplayStatics::OpenLevel(GetWorld(), FName("L_DungeonEntrance"));
	}
}

void ADungeonGameMode::HandleShush(AActor* LoudActor)
{
	if (!LoudActor)
	{
		return;
	}

	FVector SpawnLoc = LoudActor->GetActorLocation() + (LoudActor->GetActorForwardVector() * -200.0f);
	
	// Spawn the giant ear monster
	AActor* Behearer = GetWorld()->SpawnActor<AActor>(BehearerClass, SpawnLoc, FRotator::ZeroRotator);
	
	// Play the "SHHHH!" audio
	UGameplayStatics::PlaySoundAtLocation(this, ShushSound, SpawnLoc);
	
	// Apply damage
	UGameplayStatics::ApplyDamage(LoudActor, 9999.0f, nullptr, Behearer, UDamageType::StaticClass());
}

void ADungeonGameMode::BeginPlay()
{
	Super::BeginPlay();
}

UMyDungeonGameInstance* ADungeonGameMode::GetDungeonGI() const
{
	return Cast<UMyDungeonGameInstance>(GetGameInstance());
}
