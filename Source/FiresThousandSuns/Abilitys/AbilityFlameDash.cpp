#include "AbilityFlameDash.h"
#include "../FiresThousandSunsPlayerController.h"
#include "Kismet/GameplayStatics.h"

#define CD_MAXUSES	3
#define CD_DURATION	3.0

UAbilityFlameDash::UAbilityFlameDash() : UAbility() {
	this->Cooldown->SetMaxUses(CD_MAXUSES);
	this->Cooldown->SetDuration(CD_DURATION);
	this->Cooldown->Reset();
}

void	UAbilityFlameDash::Activate(FEffectParameters Parameters) {
	this->UAbility::Activate(Parameters);

	FVector instigatorLocation = Parameters.ActorInstigator->GetActorLocation();
	Parameters.CursorHitLocation.Z = instigatorLocation.Z;
	FVector directionNormalized = Parameters.CursorHitLocation - instigatorLocation;
	directionNormalized.Normalize();
	Parameters.ActorInstigator->SetActorLocation(instigatorLocation + directionNormalized * this->range);
	AFiresThousandSunsPlayerController* playerCtrl = Cast<AFiresThousandSunsPlayerController>(Parameters.ActorInstigator->GetNetOwningPlayer()->GetPlayerController(0));
	if (!playerCtrl) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("[AbilityFlameDash] PlayerController is null or cast failed."));
	} else {
		playerCtrl->StopMovement();
	}
}
