
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FiresThousandSunsPlayerState.h"
#include "FiresThousandSunsGameMode.h"

#include "FuncLib.generated.h"

#define CAST_NUM(x)	static_cast<int>(x)
//#define LOG(msg) UE_LOG(LogTemp, Warning, TEXT("[%s@line: %d] - %s"), TEXT(__FUNCTION__), __LINE__, *FString(msg))
#define LOG(func, msg) UE_LOG(LogTemp, Warning, TEXT("[%s@line: %d] %s"), *FString(func), __LINE__, *FString(msg))

#define D_(x) x
#define D(x) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, x)
#define DKEY(k, x) GEngine->AddOnScreenDebugMessage((int32)(int64)(k), 5.0f, FColor::Yellow, x)
#define WHEREAMI(k) DKEY(k, FString(__FUNCSIG__))


UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UFuncLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	//UFUNCTION(BlueprintCallable)

	UFUNCTION(BlueprintCallable)
	static void SaveThumbnail(FString ObjectPath, FString OutputPath);
	UFUNCTION(BlueprintCallable)
	static bool	CheckObject(UObject* obj, FString ErrorMsg);
	UFUNCTION(BlueprintCallable)
	static void	PrintStats(const FPlayerStatistics& Stats);
	UFUNCTION(BlueprintCallable)
	static void	CopyToClipboard(FString Input);
	UFUNCTION(BlueprintCallable)
	static FString	GetFromClipboard();

	template<typename T>
	static void	ShuffleArray(TArray<T>* arr) {
		FRandomStream RandomStream;
		RandomStream.GenerateNewSeed();
		int32 len = arr->Num();

		for (int32 i = 0; i < len; ++i) {
			int32 SwapIdx = RandomStream.RandRange(i, len - 1);
			arr->Swap(i, SwapIdx);
		}
	}

	// https://docs.oracle.com/cd/E19205-01/819-5267/6n7c46du6/index.html
	// https://nerivec.github.io/old-ue4-wiki/pages/templates-in-c.html
	template <typename T>
	static FORCEINLINE T* SafeSpawnActor(
		UWorld* TheWorld,
		UClass* ActorClass,
		const FVector& Loc = FVector(),
		const FRotator& Rot = FRotator(),
		//const bool		bNoCollisionFail = true,
		AActor* Owner = NULL,
		APawn* Instigator = NULL
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

/*
	UAbilityBar :
		- check with the BP W_Play, if we can make a func UAbilityBar::UpdatePickerPosition()
			handy way is to bind it with OnVisibilityChanged(), but it might not be the ideal way in some other context
	TODO: check actors useless tick(). PrimaryComponentTick.bCanEverTick PrimaryComponentTick.SetTickFunctionEnable(true)

	Fires :
		- GM: take fortify stacks from the buff !
		- refacto interraction buff <-> widgets (see Buff.h)
		- debug msg on logfiles
		- refacto BP / c++
		- refacto GI GM SG interactions
		- refacto inputs: migrate in PlayerController
		- flame dash drawback
		- real Widget for ability tooltips
		- Better Maven hairs...
		- visual feedback on hitting save button in settings
		- make key binding save, currently bugged ?
		~ arena UI : some background ?
		~ player death : sound
		~ trade message (with fish312/CONCESOHO ref ?)
		~ infos message (quin is the first to enter fetid pool, ben is the first to kill, carn is the first to hit lv100
		x totem skills to block suns

	cast time :
		some skills are instant and will not register for the casting
		other skills will start a delayed action that locks the player, can only have 1

		cast cancel: the delayed action has a time window where it cannot be cancelled anymore (at the end)
		determine what can be cancelled by what:
			- skills can be cancelled by player movement
			? skills can be cancelled by another skill
		anim cancel: same thing, but the action isn't cancelled, only the lock

	skill queue ? max amount or max cumulated cast time or both
*/


