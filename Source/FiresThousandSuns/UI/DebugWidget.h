#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/PanelWidget.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"

#include "DebugWidget.generated.h"



UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UDebugLine : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void	SetMessage(FString Message);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UEditableTextBox* TextBox;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;//TODO: check in other W_ if they are needed
};

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UDebugWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void	AddMessage(FString Message);
	UFUNCTION(BlueprintCallable)
	FString	GetAllContent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UVerticalBox* ContainerPanel;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UDebugLine>	LineWidgetClass = nullptr;
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
