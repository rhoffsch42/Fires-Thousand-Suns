
#pragma once

#include "Actors/Sun.h"
#include "FiresThousandSunsCharacter.h"

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
	bool	IsInitDone() const;
	UFUNCTION(BlueprintCallable)
	FVector	GetLastSpawnSideLocation() const;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	double MovementSpeedBonus = 0.38;
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
	int Waves = 17;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	int MavenCancelledSuns = 7;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	uint8	_SunsPerSide = 20;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	TSubclassOf<ASun>  SunActorClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	AFiresThousandSunsCharacter* Player;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UWorld*	World = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AActor* Maven = nullptr;//

protected:
	virtual void BeginPlay();

	bool	_IsInit = false;
	FVector	_SidePos1[4];
	FVector	_SidePos2[4];
	FVector _LastSpawnSideLocation;
private:
	void	_GrabActorsWithTags() const;
	UFUNCTION(BlueprintCallable)
	void	_CheckSunExplosion(FVector location, double damage, double radius) const;
	double	_ApplyMitigation(double damage) const;
	double	_ApplyGuardSkills(double damage) const;
	void	_SelectSunsForMavenCancellation(TArray<ASun*>* wave) const;

	uint8	_SpawnSunsCounter = 0;
};



