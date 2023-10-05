// Copyright Epic Games, Inc. All Rights Reserved.

#include "FiresThousandSunsCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "FuncLib.h"
#include "FiresThousandSunsGameInstance.h"

AFiresThousandSunsCharacter::AFiresThousandSunsCharacter() {
	// Set size for player capsule, and change collision preset
	UCapsuleComponent* capsule = GetCapsuleComponent();
	capsule->InitCapsuleSize(30.f, 96.0f);
	//capsule->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Required (or can be) in Ctor 
	this->_InitPreBeginPlay();
}

void	AFiresThousandSunsCharacter::Debug_PlayerState() {
	UFuncLib::CheckObject(this->CustomPlayerState, "AFiresThousandSunsCharacter::Debug_PlayerState() CustomPlayerState nullptr");
	APlayerState* ps = this->GetPlayerState();
	UFuncLib::CheckObject(ps, "AFiresThousandSunsCharacter::Debug_PlayerState() GetPlayerState() returned nullptr");
	AFiresThousandSunsPlayerState* casted = Cast<AFiresThousandSunsPlayerState>(this->GetPlayerState());
	UFuncLib::CheckObject(casted, "AFiresThousandSunsCharacter::Debug_PlayerState() Cast<Fires..PlayerState>() failed");
}

void	AFiresThousandSunsCharacter::_InitPreBeginPlay() {
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "AFiresThousandSunsCharacter::_InitPreBeginPlay()");
}

void	AFiresThousandSunsCharacter::_InitPostBeginPlay() {
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "AFiresThousandSunsCharacter::_InitPostBeginPlay()");
	// PlayerState
	APlayerState* ps = this->GetPlayerState();
	UFuncLib::CheckObject(ps, "AFiresThousandSunsCharacter::_InitPostBeginPlay() GetPlayerState() returned nullptr");
	this->CustomPlayerState = Cast<AFiresThousandSunsPlayerState>(this->GetPlayerState());
	if (UFuncLib::CheckObject(this->CustomPlayerState, "AFiresThousandSunsCharacter::_InitPostBeginPlay() Cast<Fires..PlayerState>() failed")) {
		//this->SetPlayerState(this->CustomPlayerState);

		UFiresThousandSunsGameInstance* FiresGI = Cast<UFiresThousandSunsGameInstance>(this->GetGameInstance());
		if (UFuncLib::CheckObject(FiresGI, "AFiresThousandSunsCharacter  GetGameInstance() or Cast<>() failed")) {
			this->UpdateStats(FiresGI->BaseStats);
		}

		// Link HealthManager to Die();
		FScriptDelegate delegateScript;
		delegateScript.BindUFunction(this, "Die");
		this->CustomPlayerState->HealthManager->HpEmpty.Add(delegateScript);
	}
}

void	AFiresThousandSunsCharacter::BeginPlay() {
	Super::BeginPlay();

	this->_InitPostBeginPlay();
}

void AFiresThousandSunsCharacter::Tick(float DeltaSeconds) {
    Super::Tick(DeltaSeconds);

}

void	AFiresThousandSunsCharacter::UpdateStats(const FPlayerStats& NewStats) {
	//AFiresThousandSunsPlayerState* state = Cast<AFiresThousandSunsPlayerState>(this->GetPlayerState());
	if (!UFuncLib::CheckObject(this->CustomPlayerState, "AFiresThousandSunsCharacter UpdateStats() CustomPlayerState is nullptr")) {
		return;
	}
	this->CustomPlayerState->PlayerStats = NewStats;
	//UFuncLib::PrintStats(NewStats);
	//UFuncLib::PrintStats(this->CustomPlayerState->PlayerStats);
	UCharacterMovementComponent* movcomp = this->GetCharacterMovement();
	if (UFuncLib::CheckObject(movcomp, "AFiresThousandSunsCharacter GetCharacterMovement() returned nullptr")) {
		movcomp->MaxWalkSpeed = 375.0 * (1.0 + NewStats.MovementSpeed);
		movcomp->MinAnalogWalkSpeed = 375.0 * (1.0 + NewStats.MovementSpeed);
	}
	this->CustomPlayerState->HealthManager->SetMaxHP(this->CustomPlayerState->PlayerStats.Life);
	this->CustomPlayerState->HealthManager->SetHP(this->CustomPlayerState->PlayerStats.Life);
}

void	AFiresThousandSunsCharacter::ApplyLifeRegen(float DeltaSeconds) {
	//this->CustomPlayerState->HealthManager->AddHP(50.0f * DeltaSeconds);
	this->CustomPlayerState->HealthManager->AddHP(this->CustomPlayerState->PlayerStats.LifeRegeneration * DeltaSeconds);
}

void	AFiresThousandSunsCharacter::Die() {
	this->PlayerDied.Broadcast();
	this->Destroy();
}
