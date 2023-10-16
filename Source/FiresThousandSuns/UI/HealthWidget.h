
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "CommonTextBlock.h"

#include "HealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class FIRESTHOUSANDSUNS_API UHealthWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void	UpdateHP(double HP, double MaxHP);
	UFUNCTION(BlueprintCallable)
	void	SetDisplayText(bool Display);
	UFUNCTION(BlueprintCallable)
	void	SetFontSize(float NewSize) const;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UProgressBar*	HealthBar;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UCommonTextBlock* HpText;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UCommonTextBlock* MaxHpText;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UCommonTextBlock* Separator;
protected:
	virtual void NativeConstruct() override;
	virtual void Tick(FGeometry MyGeometry, float InDeltaTime);

	bool	_bDisplayText = true;

private:
};
