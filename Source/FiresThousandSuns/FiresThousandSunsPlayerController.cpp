// Copyright Epic Games, Inc. All Rights Reserved.

#include "FiresThousandSunsPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "FiresThousandSunsCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FuncLib.h"

#include "GenericPlatform/GenericPlatformMath.h"

AFiresThousandSunsPlayerController::AFiresThousandSunsPlayerController() {
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;

}

void AFiresThousandSunsPlayerController::BeginPlay() {
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AFiresThousandSunsPlayerController::SetupInputComponent() {
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AFiresThousandSunsPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AFiresThousandSunsPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AFiresThousandSunsPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AFiresThousandSunsPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &AFiresThousandSunsPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &AFiresThousandSunsPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &AFiresThousandSunsPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &AFiresThousandSunsPlayerController::OnTouchReleased);
	}
}

void AFiresThousandSunsPlayerController::OnInputStarted() {
	StopMovement();
}

void AFiresThousandSunsPlayerController::OnSetDestinationTriggered() {
	if (this->bBlockInput) { return; }

	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch) {
		//bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, this->ClickCollisionChannel, true, Hit);
		bHitSuccessful = GetHitResultUnderFingerByChannel(ETouchIndex::Touch1, UEngineTypes::ConvertToTraceType(this->ClickCollisionChannel), true, Hit);
	} else {
		//bHitSuccessful = GetHitResultUnderCursor(this->ClickCollisionChannel, true, Hit);
		bHitSuccessful = GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(this->ClickCollisionChannel), true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)	{
		/*
		DKEY(this, Hit.GetActor()->GetName());
		auto parent = Hit.Component.Get()->GetAttachParent();
		if (parent) { DKEY(this + 1, parent->GetName()); }
		DKEY(this+2, Hit.BoneName.ToString());
		DKEY(this+3, FString::FromInt(this->ClickCollisionChannel.GetIntValue()));
		*/
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr) {
		FVector	distance = CachedDestination - ControlledPawn->GetActorLocation();
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("dist: %f"), distance.Length()));
		if (distance.Length() >= 110) {
			FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
		}
	}
}

void AFiresThousandSunsPlayerController::OnSetDestinationReleased() {
	if (this->bBlockInput) { return; }

	// If it was a short press
	//if (FollowTime <= ShortPressThreshold)
	//{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
	//}

	FollowTime = 0.f;
}

void AFiresThousandSunsPlayerController::OnTouchTriggered() {
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void AFiresThousandSunsPlayerController::OnTouchReleased() {
	bIsTouch = false;
	OnSetDestinationReleased();
}
