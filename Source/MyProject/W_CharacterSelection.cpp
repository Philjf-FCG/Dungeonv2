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

FText UW_CharacterSelection::GetWackyInterviewQuote(EHeroClass SelectedClass)
{
    TArray<FString> Quotes;
    
    switch (SelectedClass)
    {
        case EHeroClass::Cleric:
            Quotes.Add("The gods told me to come here. I think they're pulling a prank.");
            Quotes.Add("I'm not a 'healer', I'm a 'bio-mechanical readjuster'.");
            break;
        case EHeroClass::Thief:
            Quotes.Add("Technically, I'm just 'borrowing' the dungeon's existence.");
            Quotes.Add("Is the Behearer home? I owe him five gold and a kidney.");
            break;
        case EHeroClass::AccountingWizard:
            Quotes.Add("I have a fireball spreadsheet, but I need you to sign this waiver first.");
            Quotes.Add("I'm only here for the tax deduction. And the snacks.");
            break;
        case EHeroClass::Fighter:
        default:
            Quotes.Add("Sword goes brrrr.");
            Quotes.Add("Is the Behearer home? I want to fight them.");
            break;
    }

    if (Quotes.Num() == 0)
    {
        return FText::FromString(TEXT("Something went wrong..."));
    }
    
    int32 RandomIdx = FMath::RandRange(0, Quotes.Num() - 1);
    return FText::FromString(Quotes[RandomIdx]);
}