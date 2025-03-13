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

template UGeneratedParametersFlameDash* UAbility::PrepareGeneratedParameters<UGeneratedParametersFlameDash>(UGeneratedParameters* GeneratedParameters);

UGeneratedParametersFlameDash::UGeneratedParametersFlameDash() {}

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

	UFuncLib::CheckObject(this->GetWorld(), FSIG_APPEND(" this->GetWorld() is null"));
	UFuncLib::CheckObject(this->NiagaraSystem, FSIG_APPEND(" LoadObject<UNiagaraSystem>() failed"));
	UFuncLib::CheckObject(this->ActivationSuccessSoundCue, FSIG_APPEND(" failed to LoadObject() USoundCue"));
	UFuncLib::CheckObject(this->_NavSys, FSIG_APPEND(" could not get NavSys"));
}

bool	UAbilityFlameDash::IsActivatable(FEffectParameters& Parameters) {
	auto GenParams = this->PrepareGeneratedParameters<UGeneratedParametersFlameDash>(Parameters.GeneratedParameters);
	if (!UFuncLib::CheckObject(GenParams, FSIG_APPEND(" failed to prepare parameters"))) { return false; }
	Parameters.GeneratedParameters = GenParams;

	// calculate the target destination and direction
	FVector instigatorLocation = Parameters.ActorInstigator->GetActorLocation();
	Parameters.CursorHitLocation.Z = instigatorLocation.Z;
	GenParams->Direction = Parameters.CursorHitLocation - instigatorLocation;
	GenParams->Len = std::max(this->_minRange, std::min(this->_maxRange, GenParams->Direction.Length()));
	GenParams->Direction.Normalize();
	GenParams->TargetDest = instigatorLocation + GenParams->Direction * GenParams->Len;

	// line trace to check blocking volumes
	UWorld* world = Parameters.ActorInstigator->GetWorld();
	FHitResult Hit;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Parameters.ActorInstigator);
	world->LineTraceSingleByChannel(Hit, instigatorLocation, GenParams->TargetDest, ECollisionChannel::ECC_WorldStatic, QueryParams);

	if (Hit.bBlockingHit) {
		double hitlen = (Hit.Location - instigatorLocation).Length();
		if (hitlen < this->_minRange / 4.0) { // too close from a wall
			return false;
		}
		GenParams->Len = std::min(GenParams->Len, hitlen);
		GenParams->TargetDest = instigatorLocation + GenParams->Direction * GenParams->Len;
	}

	// place back the targetDest in the navSys
	if (UFuncLib::CheckObject(this->_NavSys, FSIG_APPEND(" NavSys not found"))) {
		FNavLocation result;
		this->_NavSys->ProjectPointToNavigation(GenParams->TargetDest, result);
		if (result.HasNodeRef()) {
			GenParams->TargetDest = result.Location;
			GenParams->TargetDest.Z = instigatorLocation.Z;
		} else {
			D(FString(FSIG_APPEND(" NavSys: no location found")));
			return false;
		}
	}
	return true;
}

// currently cannot flame dash through ECC_WorldStatic objects even if maxrange allows it.
bool	UAbilityFlameDash::Activate(FEffectParameters& Parameters) {
	if (Parameters.bRecheckActivatableOnActivate && !this->IsActivatable(Parameters)) { return false; }
	auto GenParams = this->PrepareGeneratedParameters<UGeneratedParametersFlameDash>(Parameters.GeneratedParameters);
	if (!UFuncLib::CheckObject(GenParams, FSIG_APPEND(" failed to prepare parameters"))) { return false; }

	Parameters.GeneratedParameters = GenParams;
	FVector instigatorLocation = Parameters.ActorInstigator->GetActorLocation();
	Parameters.CursorHitLocation.Z = instigatorLocation.Z;

	// place and rotate the actor
	Parameters.ActorInstigator->SetActorLocation(GenParams->TargetDest);
	FRotator rot = UKismetMathLibrary::FindLookAtRotation(instigatorLocation, Parameters.CursorHitLocation);
	Parameters.ActorInstigator->SetActorRotation(rot);
	UPlayer* owner = Parameters.ActorInstigator->GetNetOwningPlayer();
	if (UFuncLib::CheckObject(owner, FSIG_APPEND(" failed to get owner"))) {
		AFiresThousandSunsPlayerController* playerCtrl = Cast<AFiresThousandSunsPlayerController>(owner->GetPlayerController(0));
		if (UFuncLib::CheckObject(playerCtrl, FSIG_APPEND(" PlayerController is null or cast failed."))) {
			playerCtrl->StopMovement();
		}
	}

	// Movement debuff
	auto buff = UFuncLib::SafeSpawnActor<ADebuffLockedMovement>(Parameters.World, ADebuffLockedMovement::StaticClass());
	if (UFuncLib::CheckObject(buff, FSIG_APPEND(" failed to create buff with SafeSpawnActor()"))) {
		buff->SetBaseDuration(this->_lockMovementDuration);
		buff->AttachToActor(Parameters.ActorInstigator, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
		buff->ApplyTo(Parameters.ActorInstigator);
	}
	
	// Niagara visual effect
	UNiagaraComponent* Ncomp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		Parameters.ActorInstigator->GetWorld(), this->NiagaraSystem,
		instigatorLocation + GenParams->Len * 0.5 * GenParams->Direction);
	if (UFuncLib::CheckObject(Ncomp, FSIG_APPEND(" Niagara SpawnSystemAtLocation() failed "))) {
		Ncomp->SetVariableVec2("InSpriteScale", FVector2D(GenParams->Len * 0.95, 580));
		Ncomp->SetVectorParameter("InSprite1FacingVector", GenParams->Direction.Cross(FVector(0, 0, 1)));
		Ncomp->SetVectorParameter("InSprite2AlignVector", GenParams->Direction.Cross(FVector(0, 0, -1)));
		// TODO: use the built-in system in Niagara to add multiple sprites
	}

	return Super::Activate(Parameters);
}
