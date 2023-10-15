// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/VerticalBox.h"
#include "Components/WidgetSwitcher.h"
#include "Components/CanvasPanel.h"
#include "CommonTextBlock.h"
#include "Internationalization/Text.h"

#include "MenuContent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMenuContentButtonOnClicked, class UMenuContentButton*, Button);

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UMenuContentButton : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UUserWidget*	Content;
	FMenuContentButtonOnClicked OnClickedDelegate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UButton* Button;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UCommonTextBlock* ButtonText;
protected:
	virtual void NativeConstruct() override;
	UFUNCTION(BlueprintCallable)
	void OnButtonClicked();
};

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UMenuContent : public UUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void	AddMenuContent(UUserWidget* Content, FString Title);
	UFUNCTION(BlueprintCallable)
	void	AddContentAndButton(UUserWidget* Content, UMenuContentButton* Button = nullptr);

	UFUNCTION(BlueprintCallable)
	void	AddButtonOnly(UMenuContentButton* Button);
	UFUNCTION(BlueprintCallable)
	void	AddContentOnly(UUserWidget* Content);
	UFUNCTION(BlueprintCallable)
	void	LinkButtonToContent(UMenuContentButton* Button, UUserWidget* Content);
	
	UFUNCTION(BlueprintCallable)
	void	SwitchContent(UMenuContentButton* Button);
	UFUNCTION(BlueprintCallable)
	void	SetMenuWidget(UPanelWidget* Widget);
	//UFUNCTION(BlueprintCallable)
	//void	SetContentWidgetSwitcher(UWidgetSwitcher* Widget);

	UFUNCTION(BlueprintCallable)
	void	SetMenuFlex(double Value);
	UFUNCTION(BlueprintCallable)
	void	SetContentFlex(double Value);
	UFUNCTION(BlueprintCallable)
	int32	GetAmount() const;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UWidgetSwitcher* ContentWidgetSwitcher;

protected:
	virtual void Tick(FGeometry MyGeometry, float InDeltaTime);
	virtual void NativeConstruct() override;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UPanelWidget*		MenuWidget;
private:
	/*
	// construct some UWidget (not working)
	void	_construct();
	void	_debugWidgets(UCanvasPanel* Canvas, UHorizontalBox* Container, UVerticalBox* MenuBox, UWidgetSwitcher* ContentSwitche) const;
	void	_initSlotSizes(UVerticalBox* MenuBox, UHorizontalBox* Container);
	*/

};
