
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FiresThousandSunsGameInstance.h"
#include "Engine.h"

#include "FuncLib.generated.h"

#define PATH_LOGFILE_RUNTIMEERRORS	"runtime-errors.log"

#define CAST_NUM(x)	static_cast<int>(x)
#define LOG(msg) UE_LOG(LogTemp, Warning, TEXT("[%s@line: %d] %s"), *FString(__FUNCSIG__), __LINE__, *FString(msg))

#define D_(x)			x
#define D(x)			if (GEngine){GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, x);}
#define DCOL(c, x)		if (GEngine){GEngine->AddOnScreenDebugMessage(-1, 5.0f, c, x);}
#define DKEY(k, x)		if (GEngine){GEngine->AddOnScreenDebugMessage((int32)(int64)(k), 5.0f, FColor::Yellow, x);}
#define WHEREAMI(k)		DKEY(k, FString(__FUNCSIG__))
#define FSIG_APPEND(x)	FString(__FUNCSIG__).Append(x)

#define GEN_UNAME(x) MakeUniqueObjectName(x, x->StaticClass(), FName())

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UFuncLib : public UBlueprintFunctionLibrary
{  
	GENERATED_BODY()
public:
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	static UFiresThousandSunsGameInstance* Fires_GI;
	static FString LogFile;

	UFUNCTION(BlueprintCallable)
	static void SaveThumbnail(FString ObjectPath, FString OutputPath);
	UFUNCTION(BlueprintCallable)
	static bool	CheckObject(UObject* obj, FString ErrorMsg);
	UFUNCTION(BlueprintCallable)
	static void	CopyToClipboard(FString Input);
	UFUNCTION(BlueprintCallable)
	static FString	GetFromClipboard();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FString	GetLogFilePath();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FString	GetDirPaths();


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
		if (!UFuncLib::CheckObject(TheWorld, FSIG_APPEND(" error : TheWorld is null"))) {
			return nullptr;
		}
		if (!UFuncLib::CheckObject(ActorClass, FSIG_APPEND(" error : ActorClass is null"))) {
			return nullptr;
		}

		FActorSpawnParameters SpawnInfo;
		//SpawnInfo.bNoCollisionFail = bNoCollisionFail;
		SpawnInfo.Owner = Owner;
		SpawnInfo.Instigator = Instigator;
		SpawnInfo.bDeferConstruction = false;
		T* actor = TheWorld->SpawnActor<T>(ActorClass, Loc, Rot, SpawnInfo);
		if (!UFuncLib::CheckObject(actor, FSIG_APPEND(" error : SpawnActor() failed"))) {
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

	FTS :
		- check Editor warnings and errors
		- refacto BP / c++
		- refacto GI GM SG interactions
		- refacto inputs: migrate in PlayerController
		- real Widget for ability tooltips
		- Better Maven hairs...
		- visual feedback on hitting save button in settings
		~ arena UI : some background ?
		~ player death : sound
		~ trade message (with fish312/CONCESOHO ref ?)
		~ infos message (quin is the first to enter fetid pool, ben is the first to kill, carn is the first to hit lv100, the realm is shutting down in 1min
		x totem skills to block suns

	Bugs:
		- Key bindings don't save
	
	cast time :
		some skills are instant and will not register for the casting
		other skills will start a delayed action that locks the player, can only have 1

		cast cancel: the delayed action has a time window where it cannot be cancelled anymore
		determine what can be cancelled by what:
			- skills can be cancelled by player movement
			? skills can be cancelled by another skill
		anim cancel: same thing, but the action isn't cancelled, only the lock
		skill queue ? max amount, or max cumulated cast time, or both
*/
