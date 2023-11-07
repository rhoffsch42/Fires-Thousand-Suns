
#include "BuffMoltenShell.h"
#include "../FuncLib.h"
#include "Components/MeshComponent.h"

ABuffGuard::ABuffGuard() {
	this->BuffType = EBuffType::None;
}

void ABuffGuard::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);
	this->HealthManager = NewObject<UHealthManager>(this, GEN_UNAME(this)); // TODO: check all NewObject outers

	if (UFuncLib::CheckObject(this->HealthManager, "ABuffGuard() failed to create HealthManager")) {
		this->HealthManager->SetMaxHP(100);
		this->HealthManager->SetHP(100);

		FScriptDelegate script;
		script.BindUFunction(this, "OnGuardHpEmpty");
		this->HealthManager->HpEmpty.Add(script);
	}

	UFuncLib::CheckObject(this->GetWorld(), FString(__func__).Append(" GetWorld() null"));
}

FString	ABuffGuard::GetDisplayString() const {
	return FString::FromInt(this->HealthManager->GetHP());
}


void	ABuffGuard::ApplyTo(AActor* Target) {
	Super::ApplyTo(Target);
	APlayerState* PlayerState = Cast<APlayerState>(Target);
	this->_TargetPawn = PlayerState->GetPawn();
}

void	ABuffGuard::OnGuardHpEmpty() {
	this->Destroy();
}

//////////////////////////////////////////////////////////////////////

ABuffMoltenShell::ABuffMoltenShell() {
	this->BuffType = EBuffType::MoltenShell;
}

//////////////////////////////////////////////////////////////////////

ABuffVaalMoltenShell::ABuffVaalMoltenShell() {
	//WHEREAMI(-1);
	this->BuffType = EBuffType::VaalMoltenShell;
	this->Absorption = 0.39;
}

//////////////////////////////////////////////////////////////////////

ABuffSteelskin::ABuffSteelskin() {
	//WHEREAMI(-1);
	this->Absorption = 0.70;
	this->BuffType = EBuffType::Steelskin;
}

void	ABuffSteelskin::ApplyTo(AActor* Target) {
	Super::ApplyTo(Target);
	UMeshComponent* comp = this->_TargetPawn->GetComponentByClass<UMeshComponent>();
	if (UFuncLib::CheckObject(comp, "ABuffSteelskin::ApplyTo() failed to get component UMeshComponent")) {
		UMaterial* mat = LoadObject<UMaterial>(this->GetWorld(), *FString("/Script/Engine.Material'/Game/LevelPrototyping/Materials/M_Glow.M_Glow'"));
		if (UFuncLib::CheckObject(mat, "ABuffSteelskin::ApplyTo() failed to LoadObject UMaterial M_Glow.M_Glow")) {
			comp->SetOverlayMaterial(mat);
		}
	}
}

void	ABuffSteelskin::Remove() {
	Super::Remove();
	UMeshComponent* comp = this->_TargetPawn->GetComponentByClass<UMeshComponent>();
	if (UFuncLib::CheckObject(comp, "ABuffSteelskin::ApplyTo() failed to get component UMeshComponent")) {
		comp->SetOverlayMaterial(nullptr);
	}
}