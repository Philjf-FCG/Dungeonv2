#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "../W_CharacterSelection.h"
#include "../MyDungeonGameInstance.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Engine/World.h"
#include "Engine/GameInstance.h"
#include "UObject/ConstructorHelpers.h"

#include "MockCharacterSelection.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMyProjectMenuLogicTest, "MyProject.UI.Menu.Logic", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FMyProjectMenuLogicTest::RunTest(const FString& Parameters)
{
    // Create a World context for the test
    UWorld* World = UWorld::CreateWorld(EWorldType::Game, false);
    if (!World)
    {
        AddError("Failed to create UWorld for testing.");
        return false;
    }
    // FWorldContext& WorldContext = GEngine->GetWorldContextFromWorldChecked(World); // Removed: Causes crash because CreateWorld doesn't register context automatically.

    // Create a GameInstance for the World
    // We need to use UMyDungeonGameInstance specifically
    UMyDungeonGameInstance* GI = NewObject<UMyDungeonGameInstance>(World); // Transient GI
    World->SetGameInstance(GI);
    
    // Create the Mock Widget
    UMockCharacterSelection* Widget = NewObject<UMockCharacterSelection>(World);
    // Widget->SetGameInstance(GI); // Removed: UUserWidget derives GI from the World it is created in.
    // UUserWidget uses GetGameInstance() by looking at its world.
    // NewObject<UUserWidget>(World) should implicitly associate it with the world.

    // Test 1: Initial State
    TestTrue("Initial Party Empty", GI->PartySlots.Num() == 0);
    TestFalse("Launch Not Called Yet", Widget->bLaunchCalled);

    // Test 2: Select Fighter
    Widget->SelectHeroClass(EHeroClass::Fighter);
    
    TestTrue("Launch Called", Widget->bLaunchCalled);
    if (GI->PartySlots.Num() == 1)
    {
        TestTrue("Hero is Grog", GI->PartySlots[0].HeroName.ToString().Contains("Grog"));
    }
    else
    {
        AddError("Party Size incorrect after selection.");
    }

    // Cleanup
    World->DestroyWorld(false);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMyProjectMenuStructureTest, "MyProject.UI.Menu.Structure", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FMyProjectMenuStructureTest::RunTest(const FString& Parameters)
{
    // Search for likely Widget Blueprints
    TArray<FString> Candidates = {
        TEXT("/Game/NewWidgetBlueprint.NewWidgetBlueprint_C"),
        TEXT("/Game/NewWidgetBlueprint1.NewWidgetBlueprint1_C"),
        TEXT("/Game/UI/WBP_CharacterSelection.WBP_CharacterSelection_C")
    };

    bool bFoundAnyValidWidget = false;

    for (const FString& Path : Candidates)
    {
        UClass* BPClass = StaticLoadClass(UObject::StaticClass(), nullptr, *Path);
        if (BPClass && BPClass->IsChildOf(UW_CharacterSelection::StaticClass()))
        {
            AddInfo(FString::Printf(TEXT("Inspecting Widget Blueprint: %s"), *Path));
            
            // Instantate dummy to check tree
            UWorld* World = UWorld::CreateWorld(EWorldType::Game, false);
            UW_CharacterSelection* Widget = CreateWidget<UW_CharacterSelection>(World, BPClass);

            if (Widget)
            {
                bFoundAnyValidWidget = true;
                TArray<UWidget*> AllWidgets;
                Widget->WidgetTree->GetAllWidgets(AllWidgets);
                
                int32 ButtonCount = 0;
                for (UWidget* Child : AllWidgets)
                {
                    if (Child->IsA(UButton::StaticClass()))
                    {
                        ButtonCount++;
                        bool bVisible = (Child->GetVisibility() == ESlateVisibility::Visible);
                        AddInfo(FString::Printf(TEXT("  Found Button: %s (Visible: %s)"), *Child->GetName(), bVisible ? TEXT("Yes") : TEXT("No")));
                        
                        if (!bVisible)
                        {
                            AddWarning(FString::Printf(TEXT("  Button %s is hidden! User might not be able to click it."), *Child->GetName()));
                        }
                    }
                }

                if (ButtonCount == 0)
                {
                    AddWarning(FString::Printf(TEXT("  No buttons found in %s"), *Path));
                }
                else
                {
                    AddInfo(FString::Printf(TEXT("  Found %d buttons in %s. This looks like a valid menu."), ButtonCount, *Path));
                }
            }
            World->DestroyWorld(false);
        }
    }

    if (!bFoundAnyValidWidget)
    {
        AddWarning("Could not find ANY Blueprint Widget inheriting from UW_CharacterSelection in expected locations.");
    }

    return true;
}


