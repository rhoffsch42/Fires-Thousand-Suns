// Copyright Epic Games, Inc. All Rights Reserved.


#include "FiresThousandSunsGameMode.h"
#include "FiresThousandSunsPlayerController.h"
#include "FiresThousandSunsCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "EngineUtils.h"

AFiresThousandSunsGameMode::AFiresThousandSunsGameMode() {
	// use our custom PlayerController class
	PlayerControllerClass = AFiresThousandSunsPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL) {
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

void AFiresThousandSunsGameMode::BeginPlay() {
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("AFiresThousandSunsGameMode::BeginPlay()")));
}

void	AFiresThousandSunsGameMode::Init(TSubclassOf<AActor> ActorClass, FVector MinPosition, FVector MaxPosition, AFiresThousandSunsCharacter* PlayerCharacter) {
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


void	AFiresThousandSunsGameMode::SpawnSuns(Side Start, Side End) {
	if (!this->_isInit) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("Spawn positions are not initialized. Aborting."));
	} else {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, this->_sidePos1[CAST_NUM(Start)].ToString());
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, this->_sidePos2[CAST_NUM(Start)].ToString());
	}

	FVector spawn1 = this->_sidePos1[CAST_NUM(Start)];
	FVector spawn2 = this->_sidePos2[CAST_NUM(Start)];
	FVector sideVecSpawn = spawn2 - spawn1;
	FVector dest1 = this->_sidePos1[CAST_NUM(End)];
	FVector dest2 = this->_sidePos2[CAST_NUM(End)];
	FVector sideVecDest = dest2 - dest1;

	FActorSpawnParameters spawnInfo;
	FRotator rotation(0.0f, 0.0f, 0.0f);
	for (double i = 0.0; i < (double)this->_sunsPerSide; i++) {
		FVector spawnPos = spawn1 + sideVecSpawn * (i / (double)(this->_sunsPerSide - 1));// -1 because we will have suns-1 "segments" with 1 sun on each sides, starting at 0
		FVector destPos = dest1 + sideVecDest * (i / (double)(this->_sunsPerSide - 1));// -1 because we will have suns-1 "segments" with 1 sun on each sides, starting at 0
		ASun* sun = Cast<ASun>(this->GetWorld()->SpawnActor<AActor>(this->SunActorClass, spawnPos, rotation, spawnInfo));
		if (sun->IsValidLowLevel()) {
			sun->SetDestination(destPos);
			sun->bIsMoving = true;
			FScriptDelegate delegateScript;
			delegateScript.BindUFunction(this, "CheckSunExplosion");
			sun->SunExploded.Add(delegateScript);
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Spawned %d Suns"), this->_sunsPerSide));
}

void	AFiresThousandSunsGameMode::CheckSunExplosion(FVector location, double damage, double radius) const {
	FVector diff = location - this->Player->GetActorLocation();
	if (diff.Length() <= radius) {
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("[max: %lf] diff with player : %lf"), radius, diff.Length()));
		damage = tmp_applyMitigation(damage);
		double MSbefore = this->Player->MoltenShell->HealthManager->GetHP();
		this->Player->MoltenShell->HealthManager->RemoveHP(damage * this->Player->MoltenShell->ShellAbsorbtion);
		damage -= (MSbefore - this->Player->MoltenShell->HealthManager->GetHP());
		this->Player->HealthManager->RemoveHP(damage);
		this->Player->HealthManager->CheckForDeath();
	}
}

double	AFiresThousandSunsGameMode::tmp_applyMitigation(double damage) const {
	double FireResistance = 0.80;
	double SunFirePenetration = 0.00;
	double RubyFlask = 0.20;
	double SuppressionPrevention = 0.53;
	double Fortify = 0.20;
	double GlobalMitigation = 0.0;
	return damage
		* (1.0 - FireResistance + SunFirePenetration)
		* (1.0 - RubyFlask)
		* (1.0 - SuppressionPrevention)
		* (1.0 - Fortify)
		* (1.0 - GlobalMitigation)
		;
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