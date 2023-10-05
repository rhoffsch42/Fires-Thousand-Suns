// Copyright Epic Games, Inc. All Rights Reserved.


#include "FiresThousandSunsGameMode.h"
#include "FiresThousandSunsPlayerController.h"
#include "FiresThousandSunsCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "EngineUtils.h"
#include "Math/RandomStream.h"
#include "Math/UnrealMathUtility.h"
#include "FuncLib.h"
#include "FiresThousandSunsPlayerState.h"
#include "Buffs/BuffMoltenShell.h"

AFiresThousandSunsGameMode::AFiresThousandSunsGameMode() {
	// use our custom classes
	PlayerControllerClass = AFiresThousandSunsPlayerController::StaticClass();
	PlayerStateClass = AFiresThousandSunsPlayerState::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if (PlayerControllerBPClass.Class != NULL) {
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	this->World = this->GetWorld();
}

void AFiresThousandSunsGameMode::BeginPlay() {
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("AFiresThousandSunsGameMode::BeginPlay()")));
}

void	AFiresThousandSunsGameMode::Init(TSubclassOf<AActor> ActorClass, FVector MinPosition, FVector MaxPosition, UPARAM(ref) AFiresThousandSunsCharacter* PlayerCharacter) {
	this->Player = PlayerCharacter;
	this->SunActorClass = ActorClass;
	
	FVector topleft = MinPosition;
	FVector bottomRight = MaxPosition;
	FVector bottomLeft = FVector(topleft.X, bottomRight.Y, topleft.Z);
	FVector topRight = FVector(bottomRight.X, topleft.Y, topleft.Z);
	
	this->_sidePos1[CAST_NUM(Side::left)] = topleft;
	this->_sidePos2[CAST_NUM(Side::left)] = bottomLeft;
	this->_sidePos1[CAST_NUM(Side::right)] = topRight;
	this->_sidePos2[CAST_NUM(Side::right)] = bottomRight;
	this->_sidePos1[CAST_NUM(Side::top)] = topleft;
	this->_sidePos2[CAST_NUM(Side::top)] = topRight;
	this->_sidePos1[CAST_NUM(Side::bottom)] = bottomLeft;
	this->_sidePos2[CAST_NUM(Side::bottom)] = bottomRight;
	
	this->_isInit = true;
}

bool	AFiresThousandSunsGameMode::IsInitDone() const {
	return this->_isInit;
}

void	AFiresThousandSunsGameMode::SpawnSunsRegular() {
	int32	r = std::rand() % 4;
	if (r == this->_spawnSunsCounter) {
		r = (r + 5) % 4;
	}
	if (this->_spawnSunsCounter == 0) {
		this->SpawnSunsSides(Side::left, Side::right);
	} else if (this->_spawnSunsCounter == 1) {
		this->SpawnSunsSides(Side::right, Side::left);
	} else if (this->_spawnSunsCounter == 2) {
		this->SpawnSunsSides(Side::top, Side::bottom);
	} else if (this->_spawnSunsCounter == 3) {
		this->SpawnSunsSides(Side::bottom, Side::top);
	}
	this->_spawnSunsCounter = r;
}


constexpr static int SideConvToInt(Side side)  { return CAST_NUM(side); }

#define OFFSET 5.0f
void	AFiresThousandSunsGameMode::SpawnSunsSides(Side Start, Side End) {
	if (!this->_isInit) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("[Fires..GameMode] Spawn positions are not initialized. Aborting."));
	}
	FVector offsets[4] = {// a little offsets to avoid perfect mirrors suns, leading to disturbing effects for the player
		FVector(0, -OFFSET, 0),
		FVector(0, OFFSET, 0),
		FVector(-OFFSET, 0, 0),
		FVector(OFFSET, 0, 0),
	};
	int32 s = CAST_NUM(Start);
	int32 e = CAST_NUM(End);
	FVector spawn1 = this->_sidePos1[s] + offsets[s];
	FVector spawn2 = this->_sidePos2[s] + offsets[s];
	FVector sideVecSpawn = spawn2 - spawn1;
	FVector dest1 = this->_sidePos1[e] + offsets[s];
	FVector dest2 = this->_sidePos2[e] + offsets[s];
	FVector sideVecDest = dest2 - dest1;
	TArray<ASun*>	wave;
	wave.Reserve(this->_sunsPerSide);

	FActorSpawnParameters spawnInfo;
	FRotator rotation(0.0f, 0.0f, 0.0f);
	for (double i = 0.0; i < (double)this->_sunsPerSide; i++) {
		FVector spawnPos = spawn1 + sideVecSpawn * (i / (double)(this->_sunsPerSide - 1));// -1 because we will have suns-1 "segments" with 1 sun on each sides, starting at 0
		FVector destPos = dest1 + sideVecDest * (i / (double)(this->_sunsPerSide - 1));// -1 because we will have suns-1 "segments" with 1 sun on each sides, starting at 0
		ASun* sun = Cast<ASun>(this->GetWorld()->SpawnActor<AActor>(this->SunActorClass, spawnPos, rotation, spawnInfo));
		if (sun->IsValidLowLevel()) {
			sun->SetDamage(this->bIsUber ? this->UberDamage : this->Normaldamage);
			wave.Add(sun);
			sun->SetDestination(destPos);
			sun->bIsMoving = false;
			FScriptDelegate delegateScript;
			delegateScript.BindUFunction(this, "CheckSunExplosion");
			sun->SunExploded.Add(delegateScript);
		} else { GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("[Fires..GameMode] Failed to spawn ASun %d"), (int)i)); }
	}
	this->_selectSunsForMavenCancellation(&wave);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Spawned %d Suns"), this->_sunsPerSide));
}

void	AFiresThousandSunsGameMode::_selectSunsForMavenCancellation(TArray<ASun*>* wave) const {
	FRandomStream RandomStream;
	RandomStream.GenerateNewSeed();
	int32 maxIdx = wave->Num() - 1;
	for (int32 i = 0; i < this->MavenCancelledSuns; ++i)	{
		int32 SwapIdx = RandomStream.RandRange(i, maxIdx);
		wave->Swap(i, SwapIdx);
	}
	// important to do it after all the swaps to not have duplicates
	for (int32 i = 0; i < this->MavenCancelledSuns; ++i) {
		(*wave)[i]->bMavenCancelled = true;
		(*wave)[i]->SetMavenCancellationDistanceThreshold(double(i)*0.02 + (*wave)[i]->GetMavenCancellationDistanceThreshold());
	}
}

void	AFiresThousandSunsGameMode::CheckSunExplosion(FVector location, double damage, double radius) const {
	if (!this->Player->IsValidLowLevel()) { return; }
	FVector diff = location - this->Player->GetActorLocation();
	if (diff.Length() <= radius) {
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("[max: %lf] diff with player : %lf"), radius, diff.Length()));
		damage = tmp_applyMitigation(damage);

		// molten shell(s)
		UBuffManager* bm = this->Player->CustomPlayerState->GetComponentByClass<UBuffManager>();
		if (bm) {
			EBuffType types[2] = { EBuffType::VaalMoltenShell, EBuffType::MoltenShell };
			for (int32 t = 0; t < 2; t++) {
				ABuffMoltenShell* ms = Cast<ABuffMoltenShell>(bm->GetBuff(types[t])); // should be GetBuff<ABuffMoltenShell>()
				if (ms) {
					double MSbefore = ms->HealthManager->GetHP();
					ms->HealthManager->RemoveHP(damage * ms->ShellAbsorption);
					damage -= (MSbefore - ms->HealthManager->GetHP());
				}
			}
		} else { /* should not happen */ }

		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Taking damage : %lf"), damage));
		this->Player->CustomPlayerState->HealthManager->RemoveHP(damage);
	}
}

double	AFiresThousandSunsGameMode::tmp_applyMitigation(double damage) const {
	APlayerState* ps = this->Player->GetPlayerState();
	UFuncLib::CheckObject(ps, "AFiresThousandSunsGameMode::tmp_applyMitigation() GetPlayerState() returned nullptr");
	AFiresThousandSunsPlayerState* State = Cast<AFiresThousandSunsPlayerState>(ps);
	if (!UFuncLib::CheckObject(State, "AFiresThousandSunsGameMode::tmp_applyMitigation() failed to Cast PlayerState")) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("ps: %p"), ps));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("cu: %p"), this->Player->CustomPlayerState));
		return 0;
	}

	FRandomStream RandomStream;
	RandomStream.GenerateNewSeed();
	double suppRand = FMath::RandRange(0.0f, 1.0f);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::FormatAsNumber(suppRand*100));

	FPlayerStats	Stats = State->PlayerStats;
	//Stats = this->Player->CustomPlayerState->PlayerStats;
	double RubyFlask = 0.20;
	double SunFirePenetration = 0.00;
	return damage
		* (1.0 - Stats.FireResistance + SunFirePenetration)
		* (1.0 - RubyFlask)
		* (1.0 - (suppRand <= Stats.SpellSuppressionChance ? 1.0 : 0.0) * Stats.SpellSuppressionEffect) 
		* (1.0 - Stats.FortifyEffect)
		* (1.0 - Stats.CustomLessDamage)
		;
	//double FireResistance = 0.75;
	//double SpellSuppressionChance = 1.0;
	//double SpellSuppressionEffect = 0.53;
	//double Fortify = 0.20;
	//double GlobalMitigation = 0.0;
	//return damage
	//	* (1.0 - FireResistance + SunFirePenetration)
	//	* (1.0 - RubyFlask)
	//	* (1.0 - (suppRand <= SpellSuppressionChance ? 1.0 : 0.0) * SpellSuppressionEffect)
	//	* (1.0 - Fortify)
	//	* (1.0 - GlobalMitigation)
	//	;
}

 void	AFiresThousandSunsGameMode::GrabActorsWithTags() const {
	AActor *actor1 = nullptr;
	AActor *actor2 = nullptr;
	TActorIterator<AActor> ActorItr = TActorIterator<AActor>(this->GetWorld());

	// grab pin actors
	while (ActorItr) {
		//debug info, useful if this function is in a player controller class
		//ClientMessage(ActorItr->GetClass()->GetDesc());
		//ClientMessage(ActorItr->GetActorLocation().ToString());

		if (ActorItr->ActorHasTag("minPos")) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Found actor minPos")));
			actor1 = *ActorItr;
		}
		else if (ActorItr->ActorHasTag("maxPos")) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Found actor maxPos")));
			actor2 = *ActorItr;
		}

		++ActorItr;
	}

	if (!actor1 || !actor2) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Error: missing actor (BottomLeft or TopRight)")));
	}

}
