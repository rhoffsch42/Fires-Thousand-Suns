
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Blueprint/UserWidget.h"
#include "FiresThousandSunsPlayerState.h"

#include "FiresThousandSunsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FIRESTHOUSANDSUNS_API UFiresThousandSunsGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UFiresThousandSunsGameInstance();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UUserWidget*	SettingsWidget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FPlayerStats	BaseStats;
};
