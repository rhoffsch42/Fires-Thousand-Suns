
#pragma once

#include "Actors/Sun.h"
#include "FiresThousandSunsCharacter.h"
#include "FiresThousandSunsGameInstance.h"
#include "NavigationSystem.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FiresThousandSunsGameMode.generated.h"

#define PARAMS_CATEGORY		"GameSettings"
#define BP_PATH_CHARACTER	"/Game/TopDown/Blueprints/BP_Character"
#define BP_PATH_CONTROLLER	"/Game/TopDown/Blueprints/BP_PlayerController"

UENUM(BlueprintType)
enum class Side : uint8 {
	left = 0 UMETA(DisplayName = "left"),
	right UMETA(DisplayName = "right"),
	bottom UMETA(DisplayName = "bottom"),
	top UMETA(DisplayName = "top")
};

UCLASS(minimalapi)
class AFiresThousandSunsGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFiresThousandSunsGameMode();

	UFUNCTION(BlueprintCallable)
	void	Init(UPARAM(ref) TSubclassOf<AActor> ActorClassForSuns, FVector MinPosition, FVector MaxPosition,
		UPARAM(ref) AFiresThousandSunsCharacter* PlayerCharacter, UPARAM(ref) AActor* MavenActor);
	UFUNCTION(BlueprintCallable)
	FVector	PlaceBackLocationOnNavSys(FVector Location);
	UFUNCTION(BlueprintCallable)
	FVector	ClampLocationToArenaBounds(FVector HitLocation, FVector PlayerLocation) const;

	UFUNCTION(BlueprintCallable)
	bool	TrySpawnWave();
	UFUNCTION(BlueprintCallable)
	void	SpawnSunsRegular();
	UFUNCTION(BlueprintCallable)
	void	SpawnSunsSides(Side Start, Side End);
	UFUNCTION(BlueprintCallable)
	bool	IsInitDone() const;
	UFUNCTION(BlueprintCallable)
	FVector	GetLastSpawnSideLocation() const;
	UFUNCTION(BlueprintCallable)
	int32	GetWavesCounter() const;//for the current phase
	UFUNCTION(BlueprintCallable)
	int32	GetPhasesSurvived() const;

	// https://poedb.tw/us/The_Searing_Exarch#TheSearingExarchCleansingBoss

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	bool bIsUber = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	bool bIsKrangled = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	double	Normal_WavesDelay = 1.5;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	double	Uber_WavesDelay = 1.0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	double	Normal_DamageMin = 12264.0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	double	Normal_DamageMax = 18396.0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	double	Uber_DamageMin = 12871.0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	double	Uber_DamageMax = 19306.0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	int32	Normal_WavesPerPhase = 13;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	int32	Uber_WavesPerPhase = 17;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	int32	Normal_WavesSkippedBetweenPhases = 4;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	int32	Uber_WavesSkippedBetweenPhases = 7;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	int32	MavenCancelledSuns = 7;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	int32	SunsPerSide = 20;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	TSubclassOf<ASun>  SunActorClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	AFiresThousandSunsCharacter* Player = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UWorld*	World = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AActor* Maven = nullptr;

protected:
	virtual void BeginPlay();

	bool	_bIsInit = false;
	FVector	_MinPos;
	FVector	_MaxPos;
	FVector	_SidePos1[4];
	FVector	_SidePos2[4];
	FVector _LastSpawnSideLocation;
	int32	_LastSpawnSideCounter = 0;
	int32	_WaveCounter = 0;
	int32	_PhasesSurvived = 0;
	int32	_WaitCounter = 0;

	double	_WavesDelay;
	double	_DamageMin;
	double	_DamageMax;
	int32	_WavesPerPhase;
	int32	_WavesSkippedBetweenPhases;

	UNavigationSystemV1* NavSys = nullptr;
	UFiresThousandSunsGameInstance* Fires_GI = nullptr;
	USoundCue* _SunExplosionSoundCue = nullptr;
	USoundCue* _MavenCancelSoundCue = nullptr;
private:
	void	_GrabActorsWithTags() const;
	UFUNCTION(BlueprintCallable)
	void	_CheckSunExplosion(FVector location, double damage, double radius) const;
	double	_ApplyMitigation(double damage) const;
	double	_ApplyGuardSkills(double damage) const;
	void	_SelectSunsForMavenCancellation(TArray<ASun*>* wave) const;
	TArray<int32> _GenerateDestinationIndexArray() const;
};
