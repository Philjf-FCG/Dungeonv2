// W_CharacterSelection.cpp
#include "W_CharacterSelection.h"
#include "MyDungeonGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UW_CharacterSelection::SelectHeroClass(EHeroClass SelectedClass)
{
    UMyDungeonGameInstance* GI = Cast<UMyDungeonGameInstance>(GetGameInstance());
    if (!GI) return;

    // Reset the party for a fresh run
    GI->PartySlots.Empty();

    // Create the hero data based on the selection
    FHeroData NewHero;
    NewHero.ClassType = SelectedClass;
    
    // Add wacky flavor text based on class
    switch (SelectedClass)
    {
        case EHeroClass::Cleric:
            NewHero.HeroName = FText::FromString(TEXT("Brother 'Shush' Silas"));
            break;
        case EHeroClass::Thief:
            NewHero.HeroName = FText::FromString(TEXT("Sticky-Fingers Stan"));
            break;
        case EHeroClass::AccountingWizard:
            NewHero.HeroName = FText::FromString(TEXT("The Accounting Wizard"));
            break;
        case EHeroClass::Fighter:
        default:
            NewHero.HeroName = FText::FromString(TEXT("Grog the Overly-Loud"));
            break;
    }

    GI->PartySlots.Add(NewHero);
    GI->CurrentHeroIndex = 0;

    LaunchDungeon();
}

void UW_CharacterSelection::LaunchDungeon()
{
    // Load the first floor of the dungeon
    UGameplayStatics::OpenLevel(this, FName(TEXT("L_DungeonFloor_01")));
}