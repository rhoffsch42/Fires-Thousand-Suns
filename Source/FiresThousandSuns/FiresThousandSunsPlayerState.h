
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Systems/HealthManager.h"
#include "Abilitys/AbilityFlameDash.h"
#include "Abilitys/AbilityMoltenShell.h"
#include "Abilitys/AbilityManager.h"
#include "Buffs/BuffManager.h"

#include "FiresThousandSunsPlayerState.generated.h"


USTRUCT(BlueprintType)
struct FPlayerStatistics
{
	GENERATED_BODY()
	//public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32	MovementSpeed = 40;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32	Life = 6000;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32	LifeRegeneration = 200;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32	FireResistance = 75;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32	SpellSuppressionChance = 100;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32	SpellSuppressionEffect = 50;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32	FortifyEffect = 0;
};

inline bool	operator==(const FPlayerStatistics& lhs, const FPlayerStatistics& rhs) {
	bool res = (
		(lhs.MovementSpeed == rhs.MovementSpeed)
		&& (lhs.Life == rhs.Life)
		&& (lhs.LifeRegeneration == rhs.LifeRegeneration)
		&& (lhs.FireResistance == rhs.FireResistance)
		&& (lhs.SpellSuppressionChance == rhs.SpellSuppressionChance)
		&& (lhs.SpellSuppressionEffect == rhs.SpellSuppressionEffect)
		&& (lhs.FortifyEffect == rhs.FortifyEffect)
		);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString(__func__).Append(res ? " True" : " False"));
	return res;
}
inline bool operator!=(const FPlayerStatistics& lhs, const FPlayerStatistics& rhs) { return !(lhs == rhs); }


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
	FPlayerStatistics	PlayerStatistics;

	// HealtManager
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UHealthManager* HealthManager = nullptr;

	// Abilitys
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAbilityManager* AbilityManager = nullptr;

	// Flask
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UAbilityManager* FlaskManager = nullptr;

	// Buffs component
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBuffManager* BuffManager = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool	bIsDead = false;

protected:
	void	_InitPreBeginPlay();
	void	_InitPostBeginPlay();
	virtual void BeginPlay();
private:
	UAbilityFlameDash*			_FlameDash = nullptr;
	UAbilityMoltenShell*		_MoltenShell = nullptr;
	UAbilityVaalMoltenShell*	_VaalMoltenShell = nullptr;
	UAbilitySteelskin*			_Steelskin = nullptr;
};
