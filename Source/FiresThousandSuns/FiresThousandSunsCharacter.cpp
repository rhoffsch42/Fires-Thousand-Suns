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

AFiresThousandSunsCharacter::AFiresThousandSunsCharacter()
{
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

	// HealthManager
	this->HealthManager = NewObject<UHealthManager>();
	this->HealthManager->SetMaxHP(DEFAULT_PLAYER_HP);
	this->HealthManager->SetHP(DEFAULT_PLAYER_HP);
	FScriptDelegate delegateScript;
	delegateScript.BindUFunction(this, "Die");
	this->HealthManager->HpEmpty.Add(delegateScript);

	// Skills
	this->FlameDash = NewObject<UAbilityFlameDash>();
	this->FlameDash->Cooldown->World = this->GetWorld();
	
	this->MoltenShell = NewObject<UAbilityMoltenShell>();
	this->MoltenShell->Cooldown->World = this->GetWorld();
	
	this->VaalMoltenShell = NewObject<UAbilityMoltenShell>();
	this->VaalMoltenShell->ShellHP = 10000.0;
	this->VaalMoltenShell->ShellDuration = 10.8;
	this->VaalMoltenShell->ShellAbsorbtion = 0.39;
	this->VaalMoltenShell->Cooldown->World = this->GetWorld();
	this->VaalMoltenShell->Cooldown->SetDuration(60.0);
	
	// Buffs
	this->BuffManager = CreateDefaultSubobject<UBuffManager>(TEXT("BuffManager"));//must be built in the constructor, has to be done in a valid world (when the owner has a world)
}

void	AFiresThousandSunsCharacter::BeginPlay() {
	Super::BeginPlay();
	// Buffs
	//this->BuffManager = CreateDefaultSubobject<UBuffManager>(TEXT("BuffManager"));//has to be done in a valid world (so when the actor has a world)
	this->AddOwnedComponent(this->BuffManager);
	//this->BuffManager->RegisterComponent();
}

void AFiresThousandSunsCharacter::Tick(float DeltaSeconds) {
    Super::Tick(DeltaSeconds);

}

void	AFiresThousandSunsCharacter::Die() {
	this->Destroy();
}