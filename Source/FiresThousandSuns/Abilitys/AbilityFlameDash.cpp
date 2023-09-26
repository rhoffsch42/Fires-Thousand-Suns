#include "AbilityFlameDash.h"
#include "../FiresThousandSunsPlayerController.h"
#include "../Buffs/DebuffLockedMovement.h"
#include "../FuncLib.h"
#include "Kismet/GameplayStatics.h"

#define CD_MAXUSES	3
#define CD_DURATION	3.0

// explicit instanciation
template ADebuffLockedMovement* UFuncLib::SafeSpawnActor<ADebuffLockedMovement>(
	UWorld* TheWorld,
	UClass* ActorClass,
	const FVector& Loc,
	const FRotator& Rot,
	//const bool      bNoCollisionFail,
	AActor* Owner,
	APawn* Instigator
);

UAbilityFlameDash::UAbilityFlameDash() : UAbility() {
	this->Cooldown->SetMaxUses(CD_MAXUSES);
	this->Cooldown->SetDuration(CD_DURATION);
	this->Cooldown->Reset();
}

void	UAbilityFlameDash::Activate(FEffectParameters Parameters) {
	FVector instigatorLocation = Parameters.ActorInstigator->GetActorLocation();
	Parameters.CursorHitLocation.Z = instigatorLocation.Z;
	FVector direction = Parameters.CursorHitLocation - instigatorLocation;
	double len = std::max(this->_minRange, std::min(this->_maxRange, direction.Length()));
	direction.Normalize();
	Parameters.ActorInstigator->SetActorLocation(instigatorLocation + direction * len);

	AFiresThousandSunsPlayerController* playerCtrl = Cast<AFiresThousandSunsPlayerController>(Parameters.ActorInstigator->GetNetOwningPlayer()->GetPlayerController(0));
	if (!playerCtrl) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("[AbilityFlameDash] PlayerController is null or cast failed."));
	} else {
		playerCtrl->StopMovement();
	}

	ADebuffLockedMovement* buff = UFuncLib::SafeSpawnActor<ADebuffLockedMovement>(Parameters.World, ADebuffLockedMovement::StaticClass());
	buff->SetBaseDuration(this->_lockMovementDuration);
	buff->AttachToActor(Parameters.ActorInstigator, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
	buff->ApplyTo(Parameters.ActorInstigator);
	
	this->UAbility::Activate(Parameters);
}
