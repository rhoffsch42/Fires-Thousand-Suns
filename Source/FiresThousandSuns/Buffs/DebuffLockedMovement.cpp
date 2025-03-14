
#include "DebuffLockedMovement.h"
#include "../FuncLib.h"

ADebuffLockedMovement::ADebuffLockedMovement() {
	this->BuffType = EBuffType::DebuffLockedMovement;
	this->_baseDuration = 1.0;
}

void	ADebuffLockedMovement::ApplyTo(AActor* Target) {
	this->PlayerController = Cast<AFiresThousandSunsPlayerController>(Target->GetInstigatorController());
	if (UFuncLib::CheckObject(this->PlayerController, "[ADebuffLockedMovement] PlayerController is null or cast failed.")) {
		//this->PlayerController->IncrementBlockInputCounter();
		//auto comp = Cast<UAbilityManager>(this->PlayerController->GetComponentByClass(UAbilityManager::StaticClass())); comp->IncrementBlockInputCounter();
		auto playerState = this->PlayerController->GetPlayerState<AFiresThousandSunsPlayerState>(); // TMP
		playerState->AbilityManager->DecrementBlockInputCounter();
	}
	Super::ApplyTo(Target);
}

void	ADebuffLockedMovement::Remove() {
	if (this->PlayerController) {
		//this->PlayerController->DecrementBlockInputCounter();
		//auto comp = Cast<UAbilityManager>(this->PlayerController->GetComponentByClass(UAbilityManager::StaticClass())); comp->DecrementBlockInputCounter();
		auto playerState = this->PlayerController->GetPlayerState<AFiresThousandSunsPlayerState>(); // TMP
		playerState->AbilityManager->DecrementBlockInputCounter();
	}
	Super::Remove();
}
