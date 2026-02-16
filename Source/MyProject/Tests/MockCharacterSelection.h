#pragma once

#include "CoreMinimal.h"
#include "../W_CharacterSelection.h"
#include "MockCharacterSelection.generated.h"

UCLASS()
class UMockCharacterSelection : public UW_CharacterSelection
{
    GENERATED_BODY()

public:
    bool bLaunchCalled = false;

    virtual void LaunchDungeon() override
    {
        bLaunchCalled = true;
    }
};
