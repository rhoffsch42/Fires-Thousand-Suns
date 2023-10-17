
#include "BuffMoltenShell.h"

ABuffGuard::ABuffGuard() {
	this->BuffType = EBuffType::None;
	this->HealthManager = NewObject<UHealthManager>();
	this->HealthManager->SetMaxHP(100);
	this->HealthManager->SetHP(100);

	FScriptDelegate script;
	script.BindUFunction(this, "OnGuardHpEmpty");
	this->HealthManager->HpEmpty.Add(script);
}

ABuffGuard::ABuffGuard(double HP) {
	this->BuffType = EBuffType::None;
	this->HealthManager = NewObject<UHealthManager>();
	this->HealthManager->SetMaxHP(HP);
	this->HealthManager->SetHP(HP);
}

void	ABuffGuard::OnGuardHpEmpty() {
	this->Destroy();
}

//////////////////////////////////////////////////////////////////////

ABuffMoltenShell::ABuffMoltenShell() {
	this->BuffType = EBuffType::MoltenShell;
}

ABuffMoltenShell::ABuffMoltenShell(double HP) {
	this->BuffType = EBuffType::MoltenShell;
	this->HealthManager->SetMaxHP(HP);
	this->HealthManager->SetHP(HP);
}

//////////////////////////////////////////////////////////////////////

ABuffVaalMoltenShell::ABuffVaalMoltenShell() {
	this->BuffType = EBuffType::VaalMoltenShell;
	this->Absorption = 0.39;
}

ABuffVaalMoltenShell::ABuffVaalMoltenShell(double HP) {
	this->BuffType = EBuffType::VaalMoltenShell;
	this->Absorption = 0.39;
	this->HealthManager->SetMaxHP(HP);
	this->HealthManager->SetHP(HP);
}

//////////////////////////////////////////////////////////////////////

ABuffSteelskin::ABuffSteelskin() {
	this->Absorption = 0.70;
	this->BuffType = EBuffType::Steelskin;
}

ABuffSteelskin::ABuffSteelskin(double HP) {
	this->BuffType = EBuffType::Steelskin;
	this->Absorption = 0.70;
	this->HealthManager->SetMaxHP(HP);
	this->HealthManager->SetHP(HP);
}
