#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "CommonTextBlock.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Abilitys/Ability.h"

#include "AbilitySlot.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilitySlotClicked, class UAbilitySlot*, AbilitySlot);

/**
 * 
 */
UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UAbilitySlot : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void	UpdateWidget();
	UFUNCTION(BlueprintCallable)
	void	LinkAbility(UAbility* Ability);
	UFUNCTION(BlueprintCallable)
	void	UnLinkAbility();
	UFUNCTION(BlueprintCallable)
	bool	LinkInputAction(UPARAM(ref) UInputMappingContext* InputMappingContext, UPARAM(ref) UInputAction* InputAction);
	UFUNCTION(BlueprintCallable)
	void	UnLinkInputAction();

	UFUNCTION(BlueprintCallable)
	UAbility* GetLinkedAbility() const;
	UFUNCTION(BlueprintCallable)
	void	OnSlotClicked();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UButton*		Button;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UProgressBar*	CooldownBar;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UCommonTextBlock*	UseCountText;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UCommonTextBlock*	KeyBindText;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UImage*			Image;

	UPROPERTY(BlueprintAssignable, EditDefaultsOnly)
	FAbilitySlotClicked	AbilitySlotClicked;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadWrite)
	UAbility* _Ability = nullptr;
	UPROPERTY(BlueprintReadWrite)
	UInputAction* _InputAction = nullptr;

	FNumberFormattingOptions _FormatOptions;
};
