
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "FiresThousandSunsPlayerState.h"

#include "FiresThousandSunsSaveGame.generated.h"


UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UFiresThousandSunsSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static UFiresThousandSunsSaveGame* LoadSave(FString SlotName);
	UFUNCTION(BlueprintCallable)
	static UFiresThousandSunsSaveGame* CreateSave(FString SlotName, TSubclassOf<UFiresThousandSunsSaveGame> SaveGameClass);
	
	UFiresThousandSunsSaveGame();
	UFUNCTION(BlueprintCallable)
	bool	Save();
	UFUNCTION(BlueprintCallable)
	void	TryUnlockKrangledMode(int32 PhasesSurvived);

	UFUNCTION(BlueprintCallable)
	FString	ToString() const;
	UFUNCTION(BlueprintCallable)
	FString	GetSlotName() const;
	// void	SetNewSaveName(FString NewName);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString SlotName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float	MasterVolume = 0.75f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float	EffectsVolume = 0.75f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float	MusicVolume = 0.5f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float	DialoguesVolume = 0.75f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float	AmbientVolume = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FPlayerStatistics	PlayerStatistics;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<EAbilityType>	AbilityLayout;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<EAbilityType>	FlaskLayout;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool	bKrangledUnlocked = false;
protected:
private:
};
