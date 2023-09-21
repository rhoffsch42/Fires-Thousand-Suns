// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "../Systems/Cooldown.h"
typedef int32* EffectClassPtr;

#include "Ability.generated.h"

USTRUCT(BlueprintType)
struct FEffectParameters
{
	GENERATED_BODY()
//public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AActor*		ActorInstigator = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector		SpawnLocationOrSocket;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector		CursorHitLocation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<AActor*>	Targets;
};

/**
 * 
 */
UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UAbility : public UObject
{
	GENERATED_BODY()
public:
	UAbility();

	UFUNCTION(BlueprintCallable)
	void	TryActivate(FEffectParameters Parameters);
	virtual void	Activate(FEffectParameters Parameters);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCooldown*	Cooldown = nullptr;
	//FMaterial	IconMaterial;
	//SoundCue	SoundCue;
private:
};
