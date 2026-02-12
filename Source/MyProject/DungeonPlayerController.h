// DungeonPlayerController.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DungeonPlayerController.generated.h"

UCLASS()
class MYPROJECT_API ADungeonPlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    virtual void SetupInputComponent() override;

public:
    // The function bound to your "Interact" key
    UFUNCTION()
    void RequestInteraction();

    // The function to tell the Backend we are making noise
    UFUNCTION(BlueprintCallable, Category = "Backend")
    void ReportNoise(float Amount);
};