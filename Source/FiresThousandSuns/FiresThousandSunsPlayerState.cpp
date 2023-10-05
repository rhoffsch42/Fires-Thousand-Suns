
#include "FiresThousandSunsPlayerState.h"
#include "Systems/HealthManager.h"

AFiresThousandSunsPlayerState::AFiresThousandSunsPlayerState() {
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "AFiresThousandSunsPlayerState()");
	this->_Init();
}

void	AFiresThousandSunsPlayerState::_Init() {
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "AFiresThousandSunsPlayerState::_Init()");
	// HealthManager
	this->HealthManager = NewObject<UHealthManager>();
	this->HealthManager->SetMaxHP(this->PlayerStats.Life);
	this->HealthManager->SetHP(this->PlayerStats.Life);

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
	this->VaalMoltenShell->Cooldown->SetDuration(50.0);

	// Buffs
	this->BuffManager = CreateDefaultSubobject<UBuffManager>(TEXT("BuffManager"));//must be built in the constructor, has to be done in a valid world (when the owner has a world)
}

 void AFiresThousandSunsPlayerState::BeginPlay() {
	 Super::BeginPlay();

	// Buffs
	//this->BuffManager = CreateDefaultSubobject<UBuffManager>(TEXT("BuffManager"));//has to be done in a valid world (so when the actor has a world)
	this->AddOwnedComponent(this->BuffManager);
	//this->BuffManager->RegisterComponent();
}
