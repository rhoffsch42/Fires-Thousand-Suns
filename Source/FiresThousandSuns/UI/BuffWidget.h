
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Buffs/Buff.h"
#include "../Buffs/BuffMoltenShell.h"
#include "Components/Image.h"
#include "CommonTextBlock.h"

#include "BuffWidget.generated.h"

// todo: probably merge BuffValue in the BuffWidget, delete BuffGuard, inherit BuffDuration : public BuffValue. Adapt BP

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
	
	ABuff* _LinkedBuff;
private:
};

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UBuffWidgetValue : public UBuffWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UCommonTextBlock* Text;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	FNumberFormattingOptions _FormatOptions;
};

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UBuffWidgetDuration : public UBuffWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UCommonTextBlock* TextDuration;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};

UCLASS(Blueprintable)
class FIRESTHOUSANDSUNS_API UBuffWidgetGuard: public UBuffWidgetDuration
{
	GENERATED_BODY()
public:
	virtual void	LinkBuff(UPARAM(ref) ABuff* Buff);
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UCommonTextBlock* TextValue;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	FNumberFormattingOptions _FormatOptions;
	ABuffGuard* _BuffGuard;
private:
};
