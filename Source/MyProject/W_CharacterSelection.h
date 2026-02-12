// W_CharacterSelection.h
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_HeroData.h" // Our hero struct
#include "W_CharacterSelection.generated.h"

UCLASS()
class MYPROJECT_API UW_CharacterSelection : public UUserWidget
{
    GENERATED_BODY()

public:
    // This is called by your UI Buttons in Blueprint
    UFUNCTION(BlueprintCallable, Category = "Selection")
    void SelectHeroClass(EHeroClass SelectedClass);

protected:
    // Helper to start the game after selection
    void LaunchDungeon();
};