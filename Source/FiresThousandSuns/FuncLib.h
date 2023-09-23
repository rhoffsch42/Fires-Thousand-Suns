// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FuncLib.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UFuncLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	//UFUNCTION(BlueprintCallable)

	// https://docs.oracle.com/cd/E19205-01/819-5267/6n7c46du6/index.html
	// https ://nerivec.github.io/old-ue4-wiki/pages/templates-in-c.html
	template <typename T>
	static FORCEINLINE T* SafeSpawnActor(
		UWorld*			TheWorld,
		UClass*			ActorClass,
		const FVector&	Loc = FVector(),
		const FRotator&	Rot = FRotator(),
		//const bool		bNoCollisionFail = true,
		AActor*			Owner = NULL,
		APawn*			Instigator = NULL
	) {
		if (!TheWorld) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString("UFuncLib::SpawnBP() error : TheWorld is null"));
			return nullptr;
		}
		if (!ActorClass) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString("UFuncLib::SpawnBP() error : ActorClass is null"));
			return nullptr;
		}

		FActorSpawnParameters SpawnInfo;
		//SpawnInfo.bNoCollisionFail = bNoCollisionFail;
		SpawnInfo.Owner = Owner;
		SpawnInfo.Instigator = Instigator;
		SpawnInfo.bDeferConstruction = false;
		T* actor = TheWorld->SpawnActor<T>(ActorClass, Loc, Rot, SpawnInfo);
		if (!actor) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString("UFuncLib::SpawnBP() error : failed to spawn Actor"));
			return nullptr;
		}

		return actor;
	}
};
