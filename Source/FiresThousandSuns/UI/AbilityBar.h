
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySlotManager.h"

#include "AbilityBar.generated.h"


UCLASS()
class FIRESTHOUSANDSUNS_API UAbilityBar : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void	LoadAbilityManager(UAbilityManager* Manager);
	UFUNCTION(BlueprintCallable)
	void	ManagerOnClick(UAbilitySlot* InSlot);
	UFUNCTION(BlueprintCallable)
	void	PickerOnClick(UAbilitySlot* InSlot);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UAbilitySlotManager* UI_Manager;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UAbilitySlotManager* UI_Picker;

protected:
	virtual void NativeConstruct() override;

	UAbilitySlot* _LastSlotClicked = nullptr;

	UPROPERTY(BlueprintReadWrite)
	UAbilityManager* AbilityManager = nullptr;
};
