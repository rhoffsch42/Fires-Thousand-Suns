
#include "AbilityMoltenShell.h"
//#include "../FiresThousandSunsCharacter.h"
#include "../Buffs/BuffMoltenShell.h"

#define SHELL_DURATION		3.6
#define CD_MAXUSES			1
#define CD_DURATION			4.0
#define SHELL_HP			5000.0 // max 5000
#define SHELL_ABSORBTION	0.75

UAbilityMoltenShell::UAbilityMoltenShell() {
	this->Cooldown->SetMaxUses(CD_MAXUSES);
	this->Cooldown->SetDuration(CD_DURATION + SHELL_DURATION); // This Skill's Cooldown does not recover during its effect
	this->Cooldown->Reset();
}

void	UAbilityMoltenShell::Activate(FEffectParameters Parameters) {
	if (!Parameters.World) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString("UAbilityMoltenShell::Activate() error : Parameters.World is null"));
		return;
	}
	FActorSpawnParameters spawnInfo;
	AActor* spawnedActor = Parameters.World->SpawnActor<AActor>(ABuffMoltenShell::StaticClass(), spawnInfo);
	if (!spawnedActor) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString("UAbilityMoltenShell::Activate() error : SpawnActor<>() failed"));
		return;
	}
	ABuffMoltenShell* buff = Cast<ABuffMoltenShell>(spawnedActor);
	if (!buff) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString("UAbilityMoltenShell::Activate() error : Cast<>() failed"));
		return;
	}
	buff->AttachToActor(Parameters.ActorInstigator, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
	buff->HealthManager->SetMaxHP(this->ShellHP);
	buff->HealthManager->SetHP(this->ShellHP);
	buff->SetBaseDuration(this->ShellDuration);
	buff->ApplyTo(Parameters.ActorInstigator);

	this->UAbility::Activate(Parameters);
}