
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySlotManager.h"
#include "Components/CanvasPanel.h"

#include "AbilityBar.generated.h"


UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UAbilityBar : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void	LoadAbilityManager(UAbilityManager* Manager);
	void	BuildFlasksWithLayout(TArray<EAbilityType> Layout);

	UFUNCTION(BlueprintCallable)
	virtual void	ManagerOnClick(UAbilitySlot* InSlot);
	UFUNCTION(BlueprintCallable)
	virtual void	PickerOnClick(UAbilitySlot* InSlot);

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

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UFlaskBar : public UAbilityBar
{
	GENERATED_BODY()
public:
	virtual void	ManagerOnClick(UAbilitySlot* InSlot) override;
	virtual void	PickerOnClick(UAbilitySlot* InSlot) override;

protected:
	virtual void NativeConstruct() override;
};
