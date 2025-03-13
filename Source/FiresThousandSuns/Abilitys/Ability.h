#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Materials/Material.h"
#include "../Systems/Cooldown.h"
typedef int32* EffectClassPtr;
#include "Sound/SoundCue.h"

#include "Ability.generated.h"

// Any additional parameters generated during Ability activation. This class has to be inherited and specialized.
UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UGeneratedParameters : public UObject
{
	GENERATED_BODY()
public:
	UGeneratedParameters();
};

USTRUCT(BlueprintType)
struct FEffectParameters
{
	GENERATED_BODY()
//public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool		bRecheckActivatableOnActivate = false; // this is for casted (delayed) abilitys
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UWorld*		World = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AActor*		ActorInstigator = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector		SpawnLocationOrSocket;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector		CursorHitLocation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<AActor*>	Targets;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UGeneratedParameters* GeneratedParameters = nullptr;
};

UENUM(BlueprintType)
enum class EAbilityType : uint8 {
	None = 0 UMETA(DisplayName = "None"),
	FlameDash UMETA(DisplayName = "FlameDash"),
	MoltenShell UMETA(DisplayName = "MoltenShell"),
	VaalMoltenShell UMETA(DisplayName = "VaalMoltenShell"),
	Steelskin UMETA(DisplayName = "Steelskin"),
	LifeFlask UMETA(DisplayName = "LifeFlask"),
	RubyFlask UMETA(DisplayName = "RubyFlask"),
};

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UAbility : public UObject
{
	GENERATED_BODY()
public:
	UAbility();
	virtual void	PostInitProperties() override;

	UFUNCTION(BlueprintCallable)
	bool	TryActivate(FEffectParameters Parameters);// not a ref, this is intentional
	UFUNCTION(BlueprintCallable)
	virtual bool	IsActivatable(FEffectParameters& Parameters);

	UFUNCTION(BlueprintCallable)
	bool	StartCasting(FEffectParameters& Parameters);
	UFUNCTION(BlueprintCallable)
	virtual bool	Activate(FEffectParameters& Parameters);

	void	SetNewMaterial(UObject* Outer, const FString MatPath);
	template <class T>
	T* PrepareGeneratedParameters(UGeneratedParameters* GeneratedParameters) {
		T* GenParams = nullptr;

		if (GeneratedParameters) {
			GenParams = Cast<T>(GeneratedParameters);
		}
		if (!GenParams) {
			GenParams = NewObject<T>(this, MakeUniqueObjectName(this, this->StaticClass(), FName()));
		}

		return GenParams;
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCooldown*	Cooldown = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCooldown*	CastTime = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool		bIsInstant = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterial*	IconMaterial = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USoundCue* ActivationSuccessSoundCue = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USoundCue*	ActivationFailedSoundCue = nullptr;

	UPROPERTY(BlueprintReadWrite)
	EAbilityType	AbilityType = EAbilityType::None;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString			TooltipName = "Ability";
private:
};
