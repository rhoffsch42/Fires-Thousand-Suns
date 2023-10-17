
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Buffs/Buff.h"
#include "../Buffs/BuffMoltenShell.h"
#include "Components/Image.h"
#include "CommonTextBlock.h"

#include "BuffWidget.generated.h"

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UBuffWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	virtual void	LinkBuff(UPARAM(ref) ABuff* Buff);
	UFUNCTION(BlueprintCallable)
	virtual void	OnBuffExpired(ABuff* Buff);

	UFUNCTION(BlueprintCallable)
	ABuff* GetLinkedBuff() const;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UImage* Image;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UImage*	ImageBorder;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	ABuff* _LinkedBuff;
};

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UBuffWidgetGuard: public UBuffWidget
{
	GENERATED_BODY()
public:
	virtual void	LinkBuff(UPARAM(ref) ABuff* Buff);
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UCommonTextBlock* TextValue;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UCommonTextBlock* TextDuration;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	FNumberFormattingOptions _FormatOptions;
	ABuffGuard* _BuffGuard;
private:
};

// todo replace all tick() override by Mativetick() override
