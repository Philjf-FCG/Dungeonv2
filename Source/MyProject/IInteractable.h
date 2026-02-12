// IInteractable.h
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInteractable.generated.h"

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface { GENERATED_BODY() };

class MYPROJECT_API IInteractable {
    GENERATED_BODY()
public:
    // Called when the player presses the 'E' or 'Interact' key
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void OnInteract(AActor* Interactor);
};