// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Materials/Material.h"
#include "../Systems/Cooldown.h"
typedef int32* EffectClassPtr;
#include "Sound/SoundCue.h"

#include "Ability.generated.h"

USTRUCT(BlueprintType)
struct FEffectParameters
{
	GENERATED_BODY()
//public:
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
};

UENUM(BlueprintType)
enum class EAbilityType : uint8 {
	None = 0 UMETA(DisplayName = "None"),
	FlameDash UMETA(DisplayName = "MoltenShell"),
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

	UFUNCTION(BlueprintCallable)
	bool	TryActivate(FEffectParameters Parameters);
	UFUNCTION(BlueprintCallable)
	virtual bool	IsActivatable(FEffectParameters Parameters);

	UFUNCTION(BlueprintCallable)
	bool	StartCasting(FEffectParameters Parameters);
	UFUNCTION(BlueprintCallable)
	virtual bool	Activate(FEffectParameters Parameters, bool CheckActivatable = false);

	void	SetNewMaterial(UObject* Outer, const FString MatPath);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCooldown*	Cooldown = nullptr;
	UCooldown*	CastTime = nullptr;
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
