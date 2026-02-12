// DungeonPlayerController.cpp
#include "DungeonPlayerController.h"
#include "IInteractable.h"
#include "DungeonGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"

void ADungeonPlayerController::SetupInputComponent() {
    Super::SetupInputComponent();
    if (InputComponent) {
        InputComponent->BindAction("Interact", IE_Pressed, this, &ADungeonPlayerController::RequestInteraction);
    }
}

void ADungeonPlayerController::RequestInteraction() {
    APawn* MyPawn = this->GetPawn();
    if (!MyPawn) return;

    // Simple Line Trace (Raycast) to see what's in front of us
    FHitResult Hit;
    FVector Start = MyPawn->GetActorLocation();
    FVector End = Start + (MyPawn->GetActorForwardVector() * 200.0f); // 2 meters range

    if (UWorld* World = this->GetWorld()) {
        if (World->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility)) {
            AActor* HitActor = Hit.GetActor();
            if (HitActor && HitActor->GetClass()->ImplementsInterface(UInteractable::StaticClass())) {
                IInteractable::Execute_OnInteract(HitActor, MyPawn);
            }
        }
    }
}

void ADungeonPlayerController::ReportNoise(float Amount) {
    // Talk to the GameMode (The Backend Manager)
    if (this->GetWorld()) {
        if (ADungeonGameMode* GM = Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(this->GetWorld()))) {
            GM->HandleShush(this->GetPawn()); // Logic defined in previous steps
        }
    }
}