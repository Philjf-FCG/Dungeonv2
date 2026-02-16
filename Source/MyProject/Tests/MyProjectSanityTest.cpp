#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMyProjectSanityTest, "MyProject.Sanity.SimplePass", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FMyProjectSanityTest::RunTest(const FString& Parameters)
{
    TestTrue("Sanity check: True is true", true);
    return true;
}
