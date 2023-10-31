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
#include "Buffs/BuffRubyFlask.h"
#include "Kismet/GameplayStatics.h"
#include "GenericPlatform/GenericPlatformMath.h"

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
	WHEREAMI(this);
	this->Fires_GI = Cast<UFiresThousandSunsGameInstance>(this->GetGameInstance());
	UFuncLib::CheckObject(this->Fires_GI, FString(__func__).Append(" failed to get/cast game instance"));
}

void	AFiresThousandSunsGameMode::Init(
	UPARAM(ref) TSubclassOf<AActor> ActorClassForSuns,
	FVector MinPosition, FVector MaxPosition,
	UPARAM(ref) AFiresThousandSunsCharacter* PlayerCharacter,
	UPARAM(ref) AActor* MavenActor)
{
	
	this->Player = PlayerCharacter;
	this->SunActorClass = ActorClassForSuns;
	this->Maven = MavenActor;
	this->_MinPos = MinPosition;
	this->_MaxPos = MaxPosition;

	FVector topleft = MinPosition;
	FVector bottomRight = MaxPosition;
	FVector bottomLeft = FVector(topleft.X, bottomRight.Y, topleft.Z);
	FVector topRight = FVector(bottomRight.X, topleft.Y, topleft.Z);
	
	this->_SidePos1[CAST_NUM(Side::left)] = topleft;
	this->_SidePos2[CAST_NUM(Side::left)] = bottomLeft;
	this->_SidePos1[CAST_NUM(Side::right)] = topRight;
	this->_SidePos2[CAST_NUM(Side::right)] = bottomRight;
	this->_SidePos1[CAST_NUM(Side::top)] = topleft;
	this->_SidePos2[CAST_NUM(Side::top)] = topRight;
	this->_SidePos1[CAST_NUM(Side::bottom)] = bottomLeft;
	this->_SidePos2[CAST_NUM(Side::bottom)] = bottomRight;
	
	this->_SunExplosionSoundCue = LoadObject<USoundCue>(this->GetWorld(),
		*FString("/Script/Engine.SoundCue'/Game/TopDown/Blueprints/Audio/fts-sun-explosion_Cue.fts-sun-explosion_Cue'"));
	this->_MavenCancelSoundCue = LoadObject<USoundCue>(this->GetWorld(),
		*FString("/Script/Engine.SoundCue'/Game/TopDown/Blueprints/Audio/fts-maven-cancel_Cue.fts-maven-cancel_Cue'"));
	UFuncLib::CheckObject(this->_SunExplosionSoundCue, "AFiresThousandSunsGameMode::init() Failed to load sun explosion SoundCue");
	UFuncLib::CheckObject(this->_MavenCancelSoundCue, "AFiresThousandSunsGameMode::init() Failed to load Maven cancel SoundCue");

	this->_IsInit = true;
}


bool	AFiresThousandSunsGameMode::TrySpawnWave() {
	if (this->_WaveCounter == this->WavesPerPhase) {
		if (this->_WaitCounter < this->WaitBetweenPhases) {
			this->_WaitCounter++;
		} else {
			this->_PhasesSurvived++;
			this->_WaveCounter = 0;
			this->_WaitCounter = 0;
			this->Fires_GI->Fires_SG->TryUnlockKrangledMode(this->_PhasesSurvived);
		}
	} else {
		this->SpawnSunsRegular();
		return true;
	}

	return false;
}

/*
	RBRTLBRBRBRBRTRLR	BLTBTBTLTLBRBTLTR	LRBLRTRBRBLTBLTLR	RTBLTLBLBRTBLTBTR	TRBTLBRLBTLRLBTRT
	TRBRLRLRLBLTLTLTB	BRLBTLBLRTBTRLTRT	LRBLTLBTBLTRBRTRB	RLTLBLBLRTRTRTBLR	RTLRLBTLTRBTLBRLB
	RTLRTLRBTBTBLBRLB	BRLRBLRTBRLBRLRTB	LBLTLRTRTRLRTLTLBT	LRBTBTRTBRLBRLTRTR	TRLBLRLRBTRBTRBLRB
	BLBLBRTBLBLRTBTLT	LBRBLBTBLBLBRLRLRB	LBRTBTBRTLRBLBRLR	TRBLRBRLBLTBRBTBR	LBRLRLBTRLRBT	TBTRBTLBTBLRB
*/
void	AFiresThousandSunsGameMode::SpawnSunsRegular() {
	int32	r = std::rand() % 4;
	if (r == this->_LastSpawnSideCounter) {
		r = (r + 5) % 4;
	}
	if (this->_LastSpawnSideCounter == 0) {
		this->SpawnSunsSides(Side::left, Side::right);
	} else if (this->_LastSpawnSideCounter == 1) {
		this->SpawnSunsSides(Side::right, Side::left);
	} else if (this->_LastSpawnSideCounter == 2) {
		this->SpawnSunsSides(Side::top, Side::bottom);
	} else if (this->_LastSpawnSideCounter == 3) {
		this->SpawnSunsSides(Side::bottom, Side::top);
	}
	this->_LastSpawnSideCounter = r;
}

//constexpr static int SideConvToInt(Side side)  { return CAST_NUM(side); }

#define OFFSET 5.0f
void	AFiresThousandSunsGameMode::SpawnSunsSides(Side Start, Side End) {
	if (!this->_IsInit) {
		D("[Fires..GameMode] Spawn positions are not initialized. Aborting.");
		return;
	}

	this->_WaveCounter++;
	FVector offsets[4] = {// a little offsets to avoid perfect mirrors suns, leading to disturbing effects for the player
		FVector(0, -OFFSET, 0),
		FVector(0, OFFSET, 0),
		FVector(-OFFSET, 0, 0),
		FVector(OFFSET, 0, 0),
	};
	int32 s = CAST_NUM(Start);
	int32 e = CAST_NUM(End);
	FVector spawn1 = this->_SidePos1[s] + offsets[s];
	FVector spawn2 = this->_SidePos2[s] + offsets[s];
	FVector sideVecSpawn = spawn2 - spawn1;
	FVector dest1 = this->_SidePos1[e] + offsets[s];
	FVector dest2 = this->_SidePos2[e] + offsets[s];
	FVector sideVecDest = dest2 - dest1;
	this->_LastSpawnSideLocation = spawn1 + 0.5 * sideVecSpawn;

	TArray<int32>	destIndex = this->_GenerateDestinationIndexArray();
	TArray<ASun*>	wave;
	wave.Reserve(this->_SunsPerSide);

	FActorSpawnParameters spawnInfo;
	FRotator rotation(0.0f, 0.0f, 0.0f);
	for (int32 i = 0; i < this->_SunsPerSide; i++) {
		FVector spawnPos = spawn1 + sideVecSpawn * (double(i) / (double)(this->_SunsPerSide - 1));// -1 because we will have suns-1 "segments" with 1 sun on each sides, starting at 0
		FVector destPos = dest1 + sideVecDest * (double(destIndex[i]) / (double)(this->_SunsPerSide - 1));// -1 because we will have suns-1 "segments" with 1 sun on each sides, starting at 0
		ASun* sun = Cast<ASun>(this->GetWorld()->SpawnActor<AActor>(this->SunActorClass, spawnPos, rotation, spawnInfo));
		if (UFuncLib::CheckObject(sun, FString::Printf(TEXT("[Fires..GameMode] Failed to spawn ASun %d"), i))) {
			sun->SetDamage(this->bIsUber ? this->UberDamage : this->Normaldamage);
			wave.Add(sun);
			sun->SetDestination(destPos);
			sun->bIsMoving = false;
			FScriptDelegate delegateScript;
			delegateScript.BindUFunction(this, "_CheckSunExplosion");
			sun->SunExploded.Add(delegateScript);
		}
	}
	this->_SelectSunsForMavenCancellation(&wave);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Spawned %d Suns"), this->_SunsPerSide));
}

#include "DrawDebugHelpers.h"
// imperfection at the corners of the arena
FVector	AFiresThousandSunsGameMode::ClampLocationToArenaBounds(FVector HitLocation, FVector PlayerLocation) const {
	float time = 0.05f;
	HitLocation.Z = this->_MinPos.Z;// ~ player height
	FVector BoundCorrection(50, 50, 0);// because _MinPos and _MaxPos are spawn pos for suns, not actual arena bounds
	FVector clampLoc = ClampVector(HitLocation, this->_MinPos - BoundCorrection, this->_MaxPos + BoundCorrection);
	FVector clampVec = clampLoc - HitLocation;
	FVector finalIntersectionPoint = clampLoc;
	DrawDebugLine(this->Player->GetWorld(), PlayerLocation, HitLocation, FColor::Yellow, false, time);
	DrawDebugLine(this->Player->GetWorld(), HitLocation, clampLoc, FColor::Green, false, time);

	if (clampVec.SquaredLength() > 0.5f) {
		FVector clampLocDir = clampLoc - PlayerLocation;
		FVector wallDir;
		float c = 0;
		if (FGenericPlatformMath::Abs(clampVec.X) > FGenericPlatformMath::Abs(clampVec.Y)) {
			c = clampLocDir.X / clampVec.X;
			clampVec.Y = 0;
			wallDir = c * clampVec;
			c = clampVec.X / (clampVec.X - wallDir.X);
		}
		else {
			c = clampLocDir.Y / clampVec.Y;
			clampVec.X = 0;
			wallDir = c * clampVec;
			c = clampVec.Y / (clampVec.Y - wallDir.Y);
		}
		D(FString::FromInt(c*100));
		finalIntersectionPoint = FMath::Lerp(HitLocation, PlayerLocation, c);

		DrawDebugLine(this->Player->GetWorld(), PlayerLocation, PlayerLocation + wallDir, FColor::Cyan, false, time);
		//DrawDebugLine(this->Player->GetWorld(), clampLoc, playerToWall, FColor::Yellow, false, time);
		DrawDebugLine(this->Player->GetWorld(), PlayerLocation, finalIntersectionPoint, FColor::Purple, false, time, 0, 3.0f);
	}

	return finalIntersectionPoint;
}

bool	AFiresThousandSunsGameMode::IsInitDone() const { return this->_IsInit; }
FVector	AFiresThousandSunsGameMode::GetLastSpawnSideLocation() const { return this->_LastSpawnSideLocation; }
//for the current phase
int32	AFiresThousandSunsGameMode::GetWavesCounter() const { return this->_WaveCounter; }
int32	AFiresThousandSunsGameMode::GetPhasesSurvived() const { return this->_PhasesSurvived; }

//////////////////////////////////////// Private

TArray<int32>	AFiresThousandSunsGameMode::_GenerateDestinationIndexArray() const {
	TArray<int32>	destIndex;
	destIndex.SetNum(this->_SunsPerSide);
	for (int32 i = 0; i < this->_SunsPerSide; ++i) {
		destIndex[i] = i;
	}
	if (this->Fires_GI->bKrangledWaves) {
		UFuncLib::ShuffleArray<int32>(&destIndex);
	}
	return destIndex;
}

void	AFiresThousandSunsGameMode::_SelectSunsForMavenCancellation(TArray<ASun*>* wave) const {
	UFuncLib::ShuffleArray<ASun*>(wave);
	// important to do it after the suffle to not have duplicates
	for (int32 i = 0; i < this->MavenCancelledSuns; ++i) {
		(*wave)[i]->bMavenCancelled = true;
		(*wave)[i]->SetMavenCancellationDistanceThreshold(double(i)*0.01 + (*wave)[i]->GetMavenCancellationDistanceThreshold());
	}
}

void	AFiresThousandSunsGameMode::_CheckSunExplosion(FVector location, double damage, double radius) const {
	if (!this->Player->CustomPlayerState->bIsDead) {
		FVector diff = location - this->Player->GetActorLocation();
		if (diff.Length() <= radius) {
			damage = this->_ApplyMitigation(damage);
			//D_(GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::FormatAsNumber(damage)));
			damage = this->_ApplyGuardSkills(damage);
			this->Player->CustomPlayerState->HealthManager->RemoveHP(damage);
		}
	}
}

double	AFiresThousandSunsGameMode::_ApplyMitigation(double damage) const {
	APlayerState* PlayerState = this->Player->GetPlayerState();
	UFuncLib::CheckObject(PlayerState, "AFiresThousandSunsGameMode::_ApplyMitigation() GetPlayerState() returned nullptr");
	AFiresThousandSunsPlayerState* Fires_State = Cast<AFiresThousandSunsPlayerState>(PlayerState);
	if (!UFuncLib::CheckObject(Fires_State, "AFiresThousandSunsGameMode::_ApplyMitigation() failed to Cast PlayerState")) {
		UFuncLib::CheckObject(nullptr, FString::Printf(TEXT("PlayerState: %p"), PlayerState));
		UFuncLib::CheckObject(nullptr, FString::Printf(TEXT("cu: %p"), this->Player->CustomPlayerState));
		return damage; // unmitigated damage
	}
	ABuffRubyFlask* RubyFlaskBuff = Cast<ABuffRubyFlask>(Fires_State->BuffManager->GetBuff(EBuffType::RubyFlask));

	FRandomStream RandomStream;
	RandomStream.GenerateNewSeed();
	double suppRand = FMath::RandRange(0.0f, 1.0f);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::FormatAsNumber(suppRand*100));

	FPlayerStats	Stats = Fires_State->PlayerStats;
	double rubyFlaskLess = RubyFlaskBuff ? RubyFlaskBuff->LessFireDamage : 0.0;
	double sunFirePenetration = 0.00;
	double fireRes = Stats.FireResistance / 100.0;
	double finalFireRes = std::min(std::max(fireRes, 0.75), // required in case of fireRes < 75
			fireRes
			+ (RubyFlaskBuff ? RubyFlaskBuff->BonusFireResistance : 0.0)
			- sunFirePenetration
		);
	return damage
		* (1.0 - finalFireRes)
		* (1.0 - rubyFlaskLess)
		* (1.0 - (suppRand <= (Stats.SpellSuppressionChance / 100.0) ? 1.0 : 0.0) * (Stats.SpellSuppressionEffect / 100.0)) 
		* (1.0 - (Stats.FortifyEffect / 100.0))
		* (1.0 - (Stats.CustomLessDamage / 100.0))
		;
}

double	AFiresThousandSunsGameMode::_ApplyGuardSkills(double damage) const {
	UBuffManager* manager = this->Player->CustomPlayerState->GetComponentByClass<UBuffManager>();
	if (UFuncLib::CheckObject(manager, "AFiresThousandSunsGameMode::_ApplyGuardSkills() failed to get Buff Manager")) {
		EBuffType types[3] = { EBuffType::Steelskin, EBuffType::MoltenShell, EBuffType::VaalMoltenShell };
		for (int32 t = 0; t < 3; t++) {
			ABuffGuard* GuardBuff = Cast<ABuffGuard>(manager->GetBuff(types[t])); // could be GetBuff<ABuffGuard>()
			if (GuardBuff) {
				double healthBefore = GuardBuff->HealthManager->GetHP();
				GuardBuff->HealthManager->RemoveHP(damage * GuardBuff->Absorption);
				damage -= (healthBefore - GuardBuff->HealthManager->GetHP());
			}
		}
	}
	return damage;
}

 void	AFiresThousandSunsGameMode::_GrabActorsWithTags() const {
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

