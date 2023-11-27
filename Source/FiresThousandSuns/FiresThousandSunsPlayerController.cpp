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
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

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

bool	AFiresThousandSunsPlayerController::SetCastedAbility(UAbility* Ability, const FEffectParameters& InParameters) {
	if (this->_bIsCasting || !Ability) {
		//DCOL(FColor::Purple, "SetCastedAbility() refused, already casting or supplied ability is null");
		return false;
	}

	this->_CastedAbility = Ability;
	this->_Parameters = InParameters;
	this->_bIsCasting = true;
	this->IncrementBlockInputCounter();
	this->StopMovement();

	FVector	location = InParameters.CursorHitLocation;
	location.Z = InParameters.ActorInstigator->GetActorLocation().Z;
	FRotator rot = UKismetMathLibrary::FindLookAtRotation(
		InParameters.ActorInstigator->GetActorLocation(),
		location);
	InParameters.ActorInstigator->SetActorRotation(rot);
	//DCOL(FColor::Purple, FString::SanitizeFloat(Ability->CastTime->Remaining()).Append("s remaining until cast ends"));
	UKismetSystemLibrary::Delay(this->GetWorld(), Ability->CastTime->Remaining(),
		FLatentActionInfo(0, (int64)this, *FString("FinalizeCastedAbility"), this));
	return true;
}

void	AFiresThousandSunsPlayerController::FinalizeCastedAbility() {
	this->_CastedAbility->CastTime->Reset();// Delay() will not match perfectly the CastTime recharge, so we force reset to update _lastUse
	//DCOL(FColor::Purple, FString::SanitizeFloat(this->_CastedAbility->CastTime->Remaining()).Append(" (has just been reset by FinalizeCastedAbility())"));
	this->_CastedAbility->Activate(this->_Parameters);
	this->_CastedAbility = nullptr;
	this->_bIsCasting = false;
	this->DecrementBlockInputCounter();
}

void	AFiresThousandSunsPlayerController::IncrementBlockInputCounter() {
	this->_BlockInputCounter++;
	if (this->_BlockInputCounter > 0) {
		this->bBlockInput = true;
	}
}

void	AFiresThousandSunsPlayerController::DecrementBlockInputCounter() {
	this->_BlockInputCounter--;
	if (this->_BlockInputCounter == 0) {
		this->bBlockInput = false;
	} else if (this->_BlockInputCounter < 0) {
		UFuncLib::CheckObject(nullptr, FString(__FUNCSIG__).Append(" BlockInputCounter is negative"));
	}
}

bool	AFiresThousandSunsPlayerController::GetIsCasting() const { return this->_bIsCasting; }


////////////////////////// protected ////////////////////

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
		if (distance.Length() >= this->_MinimumDistanceToMove) {
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
