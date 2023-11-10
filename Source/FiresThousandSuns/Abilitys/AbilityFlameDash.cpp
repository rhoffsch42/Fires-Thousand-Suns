#include "AbilityFlameDash.h"
#include "../FiresThousandSunsPlayerController.h"
#include "../Buffs/DebuffLockedMovement.h"
#include "../FuncLib.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "CollisionQueryParams.h"


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

UAbilityFlameDash::UAbilityFlameDash() {
	this->AbilityType = EAbilityType::FlameDash;
	this->TooltipName = "Fire Dash";

	this->Cooldown->SetMaxUses(3);
	this->Cooldown->SetDuration(3.0);
	this->Cooldown->Reset();

	this->bIsInstant = false;
	this->CastTime->SetMaxUses(1);
	this->CastTime->SetDuration(0.8);
	this->CastTime->Reset();


	this->SetNewMaterial(this, FString("/Game/LevelPrototyping/Materials/fire-dash_UIMat.fire-dash_UIMat"));
	this->NiagaraSystem = LoadObject<UNiagaraSystem>(this, *FString("/Script/Niagara.NiagaraSystem'/Game/LevelPrototyping/Particles/NS_FlameDash.NS_FlameDash'"));
	this->ActivationSuccessSoundCue = LoadObject<USoundCue>(this, *FString("/Script/Engine.SoundCue'/Game/TopDown/Blueprints/Audio/fts-flame-dash_Cue.fts-flame-dash_Cue'"));
	this->_NavSys = UNavigationSystemV1::GetCurrent(this->GetWorld());

}

void	UAbilityFlameDash::PostInitProperties() {
	Super::PostInitProperties();

	UFuncLib::CheckObject(this->GetWorld(), "UAbilityFlameDash()::PostInitProperties() this->GetWorld() is null");
	UFuncLib::CheckObject(this->NiagaraSystem, FString("UAbilityFlameDash LoadObject<UNiagaraSystem>() failed"));
	UFuncLib::CheckObject(this->ActivationSuccessSoundCue, "UAbilityFlameDash UAbilitySteelskin() failed to LoadObject() USoundCue");
	UFuncLib::CheckObject(this->_NavSys, "UAbilityFlameDash()::PostInitProperties() could not get NavSys");
}

/*
	TODO: fix flame dash
	There is currently a bad design with this, it stores the precalculated destination in private variables
	but if this ability is casted (non instant), and the player tries to reuse it during the cast,
	the 2nd IsActivatable() will override the previous private variables,
	even if it's not accepted by the caster or the ability isn't activatable,
	making the first use having wrong data for the activation.

	tmp fix: the caster force the recheck by using Activate(params, true);
	real fix: store the precalculated data in the Parameters,
		we need to inherit FEffectParameters and send a pointer to be dyncast in Activate()
*/
bool	UAbilityFlameDash::IsActivatable(FEffectParameters Parameters) {
	FVector instigatorLocation = Parameters.ActorInstigator->GetActorLocation();
	Parameters.CursorHitLocation.Z = instigatorLocation.Z;
	this->_direction = Parameters.CursorHitLocation - instigatorLocation;
	this->_len = std::max(this->_minRange, std::min(this->_maxRange, this->_direction.Length()));
	this->_direction.Normalize();
	this->_targetDest = instigatorLocation + this->_direction * this->_len;

	// line trace to check blocking volumes
	UWorld* world = Parameters.ActorInstigator->GetWorld();
	FHitResult Hit;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Parameters.ActorInstigator);
	world->LineTraceSingleByChannel(Hit, instigatorLocation, this->_targetDest, ECollisionChannel::ECC_WorldStatic, QueryParams);

	if (Hit.bBlockingHit) {
		double hitlen = (Hit.Location - instigatorLocation).Length();
		if (hitlen < this->_minRange / 4.0)//too close from a wall
			return false;
		this->_len = std::min(this->_len, hitlen);
		this->_targetDest = instigatorLocation + this->_direction * this->_len;
	}

	// place back the targetDest in the navSys
	if (UFuncLib::CheckObject(this->_NavSys, "UAbilityFlameDash::Activate() NavSys not found")) {
		FNavLocation result;
		this->_NavSys->ProjectPointToNavigation(this->_targetDest, result);
		if (result.HasNodeRef()) {
			this->_targetDest = result.Location;
			this->_targetDest.Z = instigatorLocation.Z;
		} else {
			D(FString("UAbilityFlameDash::Activate() NavSys: no location found"));
			return false;
		}
	}
	return true;
}

// currently cannot flame dash through static even if maxrange allows it.
bool	UAbilityFlameDash::Activate(FEffectParameters Parameters, bool bCheckActivatable) {
	if (bCheckActivatable && !this->IsActivatable(Parameters)) { return false; }

	FVector instigatorLocation = Parameters.ActorInstigator->GetActorLocation();
	Parameters.CursorHitLocation.Z = instigatorLocation.Z;

	// place and rotate the actor
	Parameters.ActorInstigator->SetActorLocation(this->_targetDest);
	FRotator rot = UKismetMathLibrary::FindLookAtRotation(instigatorLocation, Parameters.CursorHitLocation);
	Parameters.ActorInstigator->SetActorRotation(rot);
	UPlayer* owner = Parameters.ActorInstigator->GetNetOwningPlayer();
	if (!UFuncLib::CheckObject(owner, "[AbilityFlameDash] failed to get owner")) { return false; }
	AFiresThousandSunsPlayerController* playerCtrl = Cast<AFiresThousandSunsPlayerController>(owner->GetPlayerController(0));
	if (UFuncLib::CheckObject(playerCtrl, "[AbilityFlameDash] PlayerController is null or cast failed.")) {
		playerCtrl->StopMovement();
	}

	// Movement debuff
	ADebuffLockedMovement* buff = UFuncLib::SafeSpawnActor<ADebuffLockedMovement>(Parameters.World, ADebuffLockedMovement::StaticClass());
	if (!UFuncLib::CheckObject(buff, " [AbilityFlameDash] buff is null")) { return false; }
	buff->SetBaseDuration(this->_lockMovementDuration);
	buff->AttachToActor(Parameters.ActorInstigator, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
	buff->ApplyTo(Parameters.ActorInstigator);
	
	// Niagara visual effect
	UNiagaraComponent* Ncomp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		Parameters.ActorInstigator->GetWorld(), this->NiagaraSystem, instigatorLocation + this->_len * 0.5 * this->_direction);
	if (UFuncLib::CheckObject(Ncomp, "[UAbilityFlameDash] Niagara SpawnSystemAtLocation() failed ")) {
		Ncomp->SetVariableVec2("InSpriteScale", FVector2D(this->_len * 0.95, 580));
		Ncomp->SetVectorParameter("InSprite1FacingVector", this->_direction.Cross(FVector(0, 0, 1)));
		Ncomp->SetVectorParameter("InSprite2AlignVector", this->_direction.Cross(FVector(0, 0, -1)));
	}

	return Super::Activate(Parameters);
}
