
#include "BuffMoltenShell.h"

#define DEFAULT_SHELL_HP	100.0

ABuffMoltenShell::ABuffMoltenShell() {
	this->PrimaryActorTick.bCanEverTick = false;

	this->BuffType = EBuffType::MoltenShell;

	// HealthManager
	this->HealthManager = NewObject<UHealthManager>();
	this->HealthManager->SetMaxHP(DEFAULT_SHELL_HP);
	this->HealthManager->SetHP(DEFAULT_SHELL_HP);
}

ABuffMoltenShell::ABuffMoltenShell(double HP) {
	this->PrimaryActorTick.bCanEverTick = false;

	// HealthManager
	this->HealthManager = NewObject<UHealthManager>();
	this->HealthManager->SetMaxHP(HP);
	this->HealthManager->SetHP(HP);
}

void	ABuffMoltenShell::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
