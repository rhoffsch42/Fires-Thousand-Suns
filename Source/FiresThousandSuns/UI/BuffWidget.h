
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "../Buffs/Buff.h"

#include "BuffWidget.generated.h"

/**
 * 
 */
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
	virtual void Tick(FGeometry MyGeometry, float InDeltaTime);

private:
	ABuff* _LinkedBuff;
};
