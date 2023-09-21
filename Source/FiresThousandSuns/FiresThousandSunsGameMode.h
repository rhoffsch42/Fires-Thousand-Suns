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
	void	SpawnSuns(Side Start, Side End);
	UFUNCTION(BlueprintCallable)
	void	Init(TSubclassOf<AActor> ActorClass, FVector MinPosition, FVector MaxPosition, AFiresThousandSunsCharacter* PlayerCharacter);
	UFUNCTION(BlueprintCallable)
	bool	IsInitDone() const;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	int Waves = 5;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	uint8	_sunsPerSide = 20;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	TSubclassOf<ASun>  SunActorClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PARAMS_CATEGORY)
	AFiresThousandSunsCharacter* Player;

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
};



