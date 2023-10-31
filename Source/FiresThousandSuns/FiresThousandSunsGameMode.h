
#pragma once

#include "Actors/Sun.h"
#include "FiresThousandSunsCharacter.h"
#include "FiresThousandSunsGameInstance.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FiresThousandSunsGameMode.generated.h"

#define PARAMS_CATEGORY	"GameSettings"

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
	void	SpawnSunsRegular();
	UFUNCTION(BlueprintCallable)
	void	SpawnSunsSides(Side Start, Side End);
	UFUNCTION(BlueprintCallable)
	void	Init(UPARAM(ref) TSubclassOf<AActor> ActorClassForSuns, FVector MinPosition, FVector MaxPosition,
		UPARAM(ref) AFiresThousandSunsCharacter* PlayerCharacter, UPARAM(ref) AActor* MavenActor);
	UFUNCTION(BlueprintCallable)
	FVector	ClampLocationToArenaBounds(FVector HitLocation, FVector PlayerLocation) const;
	UFUNCTION(BlueprintCallable)
	bool	IsInitDone() const;
	UFUNCTION(BlueprintCallable)
	bool	TrySpawnWave();
	UFUNCTION(BlueprintCallable)
	FVector	GetLastSpawnSideLocation() const;
	UFUNCTION(BlueprintCallable)
	int32	GetWavesCounter() const;//for the current phase
	UFUNCTION(BlueprintCallable)
	int32	GetPhasesSurvived() const;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	double MovementSpeedBonus = 0.38;//TODO: check if it's still in use, it shouldn't
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	bool bIsUber = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	double WavesDelayNormal = 1.5;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	double WavesDelayUber = 1.0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	double	UberDamage = 17355.0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	double	Normaldamage = 16557.0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	int WavesPerPhase = 17;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	int MavenCancelledSuns = 7;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	int32	_SunsPerSide = 20;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	int32	WaitBetweenPhases = 7;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	TSubclassOf<ASun>  SunActorClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	AFiresThousandSunsCharacter* Player;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UWorld*	World = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AActor* Maven = nullptr;

protected:
	virtual void BeginPlay();

	bool	_IsInit = false;
	FVector	_MinPos;
	FVector	_MaxPos;
	FVector	_SidePos1[4];
	FVector	_SidePos2[4];
	FVector _LastSpawnSideLocation;
	int32	_LastSpawnSideCounter = 0;
	int32	_WaveCounter = 0;
	int32	_PhasesSurvived = 0;
	int32	_WaitCounter = 0;

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
