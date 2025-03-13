#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySlot.h"
#include "Abilitys/AbilityManager.h"
#include "Components/Widget.h"
#include "Components/HorizontalBox.h"

#include "AbilitySlotManager.generated.h"

//#define TESTS_IABILITYMANAGER

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilitySlotClicked, class UAbilitySlot*, AbilitySlot);

// todo : replace UAbility by any Widget ! rename this to ObjectManager / Inventory 

UINTERFACE(Blueprintable)
class FIRESTHOUSANDSUNS_API UAbilitySlotManagerInterface : public UInterface
{
	GENERATED_BODY()
};

class FIRESTHOUSANDSUNS_API IAbilitySlotManagerInterface
{
	GENERATED_BODY()
	//GENERATED_UINTERFACE_BODY()
public:
	UFUNCTION(NotBlueprintable)
	virtual UPanelSlot* AddSlot(UAbilitySlot* NewSlot) = 0;
protected:
private:
};

UCLASS()
class FIRESTHOUSANDSUNS_API UAbilitySlotManager : public UUserWidget, public IAbilitySlotManagerInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	virtual void	SetSlotClass(TSubclassOf<UAbilitySlot> Class);
	UFUNCTION(BlueprintCallable)
	virtual void	LinkAbilityManager(UAbilityManager* InManager);
	UFUNCTION(BlueprintCallable)
	void			LinkSlotsWithInputActions(UInputMappingContext* InputMappingContext, TArray<UInputAction*> InputActionArray);

	UFUNCTION(BlueprintCallable)
	virtual void	ClearContainer() const;
	UFUNCTION(BlueprintCallable)
	virtual UAbilitySlot* CreateNewSlot();
	virtual UPanelSlot* AddSlot(UAbilitySlot* NewSlot) override;
	UFUNCTION(BlueprintCallable)
	void	SetLayout(const TArray<EAbilityType> Layout, bool UsingCopys = false);

	UFUNCTION(BlueprintCallable)
	TArray<EAbilityType>	GetLayoutAsAbilityType() const;
	UFUNCTION(BlueprintCallable)
	virtual UAbilityManager* GetLinkedAbilityManager() const;

#ifdef TESTS_IABILITYMANAGER
	//UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void	TEST_ReplaceRoot();
	//UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DebugRoot();
#endif

	/*
		Can be one of : UPanelWidget, UCanvasPanel, UCommonWidgetCarousel, UContentWidget, UGridPanel,
		UHorizontalBox, UOverlay, UScrollBox, UUniformGridPanel, UVerticalBox, UWidgetSwitcher, UWrapBox
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UPanelWidget* ContainerPanel;
protected:
	TSubclassOf<UAbilitySlot>	_SlotClass;
	TArray<UAbilitySlot*>		_Slots;
	UAbilityManager* _Manager = nullptr;

	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
private:
};

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UAbilitySlotManagerHBox : public UAbilitySlotManager
{
	GENERATED_BODY()
public:
	virtual UPanelSlot*	AddSlot(UAbilitySlot* NewSlot) override;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	//UHorizontalBox* ContainerHBox = nullptr;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
private:
};
