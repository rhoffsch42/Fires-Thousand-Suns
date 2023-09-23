// Fill out your copyright notice in the Description page of Project Settings.


#include "DebuffLockedMovement.h"
//#include "../AFiresThousandSunsPlayerController.h"

ADebuffLockedMovement::ADebuffLockedMovement() {
	this->BuffType = EBuffType::DebuffLockedMovement;
	this->_baseDuration = 1.0;
}

void	ADebuffLockedMovement::ApplyTo(AActor* Target) {
	//APlayerController* playerCtrl = Cast<APlayerController>(Target->GetInstigatorController());
	AController* ctrl = Target->GetInstigatorController();
	ctrl->bBlockInput = true;

	Super::ApplyTo(Target);
}

void	ADebuffLockedMovement::Remove() {
	AController* ctrl = this->_target->GetInstigatorController();
	ctrl->bBlockInput = false;

	Super::Remove();
}
