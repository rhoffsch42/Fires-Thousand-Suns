// Copyright Epic Games, Inc. All Rights Reserved.

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
#define CAST_NUM(x)	static_cast<int>(x)


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
	void	Init(TSubclassOf<AActor> ActorClass, FVector MinPosition, FVector MaxPosition, AFiresThousandSunsCharacter* PlayerCharacter);
	UFUNCTION(BlueprintCallable)
	bool	IsInitDone() const;


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
	uint8	_sunsPerSide = 20;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	TSubclassOf<ASun>  SunActorClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	AFiresThousandSunsCharacter* Player;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UWorld*	World = nullptr;

protected:
	virtual void BeginPlay();

	bool	_isInit = false;
	FVector	_sidePos1[4];
	FVector	_sidePos2[4];
private:
	void	GrabActorsWithTags() const;
	UFUNCTION(BlueprintCallable)
	void	CheckSunExplosion(FVector location, double damage, double radius) const;
	double	tmp_applyMitigation(double damage) const;
	void	_selectSunsForMavenCancellation(TArray<ASun*>* wave) const;

	uint8	_spawnSunsCounter = 0;
};



