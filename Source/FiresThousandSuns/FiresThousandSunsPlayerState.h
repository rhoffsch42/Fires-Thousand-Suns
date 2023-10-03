
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FiresThousandSunsPlayerState.generated.h"


USTRUCT(BlueprintType)
struct FPlayerStats
{
	GENERATED_BODY()
	//public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	double	MovementSpeed = 0.35;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	double	Life = 6000.0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	double	LifeRegeneration = 500.0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	double	FireResistance = 0.75;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	double	SpellSuppressionChance = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	double	SpellSuppressionEffect = 0.5;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	double	FortifyStacks = 0.0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	double	CustomLessDamage = 0.0;
};


/**
 * 
 */
UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API AFiresThousandSunsPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	AFiresThousandSunsPlayerState();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FPlayerStats	PlayerStats;
//protected:
	//virtual void BeginPlay();
};
