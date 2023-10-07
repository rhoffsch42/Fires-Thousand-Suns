#include "AbilityFlameDash.h"
#include "../FiresThousandSunsPlayerController.h"
#include "../Buffs/DebuffLockedMovement.h"
#include "../FuncLib.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

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


	// Niagara visual effect
	UNiagaraComponent* Ncomp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		Parameters.ActorInstigator->GetWorld(), this->NiagaraSystem, instigatorLocation + len * 0.5 * direction);
	if (UFuncLib::CheckObject(Ncomp, "[UAbilityFlameDash] Niagara SpawnSystemAtLocation() failed ")) {
		Ncomp->SetVariableVec2("InSpriteScale", FVector2D(len*0.95, 580));
		Ncomp->SetVectorParameter("InSprite1FacingVector", direction.Cross(FVector(0, 0, 1)));
		Ncomp->SetVectorParameter("InSprite2AlignVector", direction.Cross(FVector(0, 0, -1)));
	}

	// Player displacement
	Parameters.ActorInstigator->SetActorLocation(instigatorLocation + direction * len);
	FRotator rot = UKismetMathLibrary::FindLookAtRotation(instigatorLocation, Parameters.CursorHitLocation);
	Parameters.ActorInstigator->SetActorRotation(rot);
	AFiresThousandSunsPlayerController* playerCtrl = Cast<AFiresThousandSunsPlayerController>(Parameters.ActorInstigator->GetNetOwningPlayer()->GetPlayerController(0));
	if (!playerCtrl) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("[AbilityFlameDash] PlayerController is null or cast failed."));
	} else {
		playerCtrl->StopMovement();
	}

	// Movement debuff
	ADebuffLockedMovement* buff = UFuncLib::SafeSpawnActor<ADebuffLockedMovement>(Parameters.World, ADebuffLockedMovement::StaticClass());
	buff->SetBaseDuration(this->_lockMovementDuration);
	buff->AttachToActor(Parameters.ActorInstigator, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
	buff->ApplyTo(Parameters.ActorInstigator);
	
	this->UAbility::Activate(Parameters);
}
