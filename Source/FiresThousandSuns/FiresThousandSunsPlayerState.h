
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Systems/HealthManager.h"
#include "Abilitys/AbilityFlameDash.h"
#include "Abilitys/AbilityMoltenShell.h"
#include "Buffs/BuffManager.h"

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
	double	FortifyEffect = 0.0;
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

	// HealtManager
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UHealthManager* HealthManager = nullptr;

	// Skills
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAbilityFlameDash* FlameDash = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAbilityMoltenShell* MoltenShell = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAbilityMoltenShell* VaalMoltenShell = nullptr;

	// Buffs component
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBuffManager* BuffManager = nullptr;

protected:
	void	_Init();
	virtual void BeginPlay();
};
