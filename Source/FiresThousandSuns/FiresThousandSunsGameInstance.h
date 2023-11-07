
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Blueprint/UserWidget.h"
#include "FiresThousandSunsPlayerState.h"
#include "FiresThousandSunsSaveGame.h"

#include "FiresThousandSunsGameInstance.generated.h"


UCLASS()
class FIRESTHOUSANDSUNS_API UFiresThousandSunsGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UFiresThousandSunsGameInstance();

	UFUNCTION(BlueprintCallable)
	void	InitSaveGame(FString SaveName, TSubclassOf<UFiresThousandSunsSaveGame> SaveGameClass);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UFiresThousandSunsSaveGame* Fires_SG = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UUserWidget*	UserWidgetRef = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FPlayerStatistics	BaseStats;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<EAbilityType>	AbilityLayout;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<EAbilityType>	FlaskLayout;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool	bUberMode = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool	bKrangledWaves = false;

};
